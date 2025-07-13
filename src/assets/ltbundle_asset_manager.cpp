#ifdef _WIN32
#include <Winsock2.h>
#else
#include <arpa/inet.h>
#endif

#include <LTEngine/hash.hpp>

#include <LTEngine/assets/ltbundle_asset_manager.hpp>

#include <LTEngine/exceptions/exc_already_exists.hpp>
#include <LTEngine/exceptions/exc_corrupt_data.hpp>
#include <LTEngine/exceptions/exc_invalid_argument.hpp>
#include <LTEngine/exceptions/exc_invalid_data.hpp>
#include <LTEngine/exceptions/exc_not_found.hpp>


using namespace LTEngine;

inline u64 ntohll(u64 val) {
	return ((u64)ntohl((val >> 32) & 0xFFFFFFFF) << 32) | ntohl(val & 0xFFFFFFFF);
}

inline u64 htonll(u64 val) {
	return ((u64)htonl((val >> 32) & 0xFFFFFFFF) << 32) | htonl(val & 0xFFFFFFFF);
}

const u16 LTBUNDLE_VERSION = 0;
const u64 LTBUNDLE_MAGIC = ((u64)'L' << 56) | ((u64)'T' << 48) | ((u64)'E' << 40) | ((u64)'B' << 32) | ('N' << 24) | ('\0' << 16) | LTBUNDLE_VERSION;

LTENGINE_PACK_START()

struct LTBundleHeader {
	u64 magic = LTBUNDLE_MAGIC;

	u32 asset_count = 0;
} LTENGINE_PACK_END();

LTENGINE_PACK_START()

struct LTBundleAssetEntry {
	u32 path_size;
	u64 size;
	u32 checksum;
} LTENGINE_PACK_END();

LTBundleAssetManager::LTBundleAssetManager(LTEngine::OS::File *file)
    : _file(file) {
}

const std::vector<u8> LTBundleAssetManager::load_asset_pure(std::string path) {
	if (!(_file->get_mode() & OS::File::FLAG_FILE_READ)) {
		throw InvalidArgumentException("Cannot load without read mode file!");
	}

	_file->seekp(0, OS::File::Seek::BEGIN);
	size_t file_size = _file->size();

	if (file_size < sizeof(LTBundleHeader)) {
		throw CorruptDataException("Header is too small!");
	}

	LTBundleHeader header;
	_file->read(&header, sizeof(LTBundleHeader));

	if (header.magic != LTBUNDLE_MAGIC) {
		throw CorruptDataException("Invalid magic!");
	}

	for (u32 i = 0; i < ntohl(header.asset_count); i++) {
		LTBundleAssetEntry entry;
		_file->read(&entry, sizeof(LTBundleAssetEntry));

		if (_file->tellg() + ntohl(entry.path_size) > file_size) {
			throw CorruptDataException("Entry path size too large!");
		}

		std::string entry_path;
		entry_path.resize(ntohl(entry.path_size));
		_file->read(entry_path.data(), ntohl(entry.path_size));

		if (entry_path == path) {
			if (_file->tellg() + ntohl(entry.size) > file_size) {
				throw CorruptDataException("Entry size is too large!");
			}

			std::vector<u8> data(ntohll(entry.size));
			_file->read(data.data(), ntohll(entry.size));
			if (entry.checksum != Hash::crc32(data.data(), ntohll(entry.size))) {
				throw CorruptDataException("Asset " + path + " is corrupt!");
			}
			return data;
		}
		// Advance forward past data or data will be read as an entry header
		_file->seekg(ntohll(entry.size), OS::File::Seek::CURRENT);
	}
	throw NotFoundException("Asset " + path + " not found!");
}

void LTBundleAssetManager::save_asset_pure(std::string path, const u8 *data, size_t size, bool correct_errors) {
	if (_file->get_mode() & OS::File::FLAG_FILE_APPEND) {
		throw InvalidArgumentException("Cannot save to append mode file!");
	}
	if (!(_file->get_mode() & OS::File::FLAG_FILE_READ) || !(_file->get_mode() & OS::File::FLAG_FILE_WRITE)) {
		throw InvalidArgumentException("Cannot save without read/write mode file!");
	}
	_file->seekp(0, OS::File::Seek::BEGIN);
	size_t file_size = _file->size();

	// Check if an existing header exists
	LTBundleHeader header;
	if (file_size < sizeof(LTBundleHeader)) {
		header = {};
		_file->seekp(sizeof(LTBundleHeader), OS::File::Seek::BEGIN);
	} else {
		_file->read(&header, sizeof(LTBundleHeader));
		header.asset_count = ntohl(header.asset_count);
	}

	std::vector<LTBundleAssetEntry> entries;
	std::vector<std::string> paths;
	std::vector<std::vector<u8>> assets_data;

	if (header.magic == LTBUNDLE_MAGIC) {
		for (u32 i = 0; i < header.asset_count; i++) {
			bool errored = false;

			LTBundleAssetEntry entry;
			_file->read(&entry, sizeof(LTBundleAssetEntry));

			std::string entry_path;
			if (_file->tellg() + ntohl(entry.path_size) > file_size) {
				if (!correct_errors) {
					throw CorruptDataException("Entry path size too large!");
				}
				errored = true;
				_file->seekg(ntohl(entry.path_size), OS::File::Seek::CURRENT);
			} else {
				entry_path.resize(ntohl(entry.path_size));
				_file->read(entry_path.data(), ntohl(entry.path_size));
				if (entry_path == path) {
					errored = true;
				}
			}

			std::vector<u8> data(ntohll(entry.size));
			if (_file->tellg() + ntohll(entry.size) > file_size) {
				if (!correct_errors) {
					throw CorruptDataException("Entry size is too large!");
				}
				errored = true;
				_file->seekg(ntohll(entry.size), OS::File::Seek::CURRENT);
			} else {
				_file->read(data.data(), ntohll(entry.size));
				if (entry.checksum != Hash::crc32(data.data(), ntohll(entry.size))) {
					if (!correct_errors) {
						throw CorruptDataException("Asset " + path + " is corrupt!");
					}
					errored = true;
				}
			}

			if (!errored) {
				entries.push_back(entry);
				paths.push_back(entry_path);
				assets_data.push_back(data);
			}
		}
	} else {
		header = {};
	}

	LTBundleAssetEntry entry;
	entry.path_size = htonl(path.size());
	entry.size = htonll(size);
	entry.checksum = Hash::crc32(data, size);

	entries.push_back(entry);
	paths.push_back(path);

	std::vector<u8> asset_data(size);
	memcpy(asset_data.data(), data, size);
	assets_data.push_back(asset_data);

	header.asset_count = htonl(entries.size());

	_file->clear();
	_file->seekp(0, OS::File::Seek::BEGIN);

	_file->write(&header, sizeof(LTBundleHeader));
	for (u32 i = 0; i < ntohl(header.asset_count); i++) {
		_file->write((u8 *)&entries[i], sizeof(LTBundleAssetEntry));
		_file->write(paths[i].data(), ntohl(entries[i].path_size));
		_file->write(assets_data[i].data(), assets_data[i].size());
	}
}
