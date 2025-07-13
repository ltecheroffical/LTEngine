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

	u32 assetCount = 0;
} LTENGINE_PACK_END();

LTENGINE_PACK_START()

struct LTBundleAssetEntry {
	u32 pathSize;
	u64 size;
	u32 checksum;
} LTENGINE_PACK_END();

LTBundleAssetManager::LTBundleAssetManager(LTEngine::OS::File *file)
    : m_file(file) {
}

const std::vector<u8> LTBundleAssetManager::loadAssetPure(std::string path) {
	if (!(m_file->getMode() & OS::File::FLAG_FILE_READ)) {
		throw InvalidArgumentException("Cannot load without read mode file!");
	}

	m_file->seekp(0, OS::File::Seek::Begin);
	size_t fileSize = m_file->size();

	if (fileSize < sizeof(LTBundleHeader)) {
		throw CorruptDataException("Header is too small!");
	}

	LTBundleHeader header;
	m_file->read(&header, sizeof(LTBundleHeader));

	if (header.magic != LTBUNDLE_MAGIC) {
		throw CorruptDataException("Invalid magic!");
	}

	for (u32 i = 0; i < ntohl(header.assetCount); i++) {
		LTBundleAssetEntry entry;
		m_file->read(&entry, sizeof(LTBundleAssetEntry));

		if (m_file->tellg() + ntohl(entry.pathSize) > fileSize) {
			throw CorruptDataException("Entry path size too large!");
		}

		std::string entryPath;
		entryPath.resize(ntohl(entry.pathSize));
		m_file->read(entryPath.data(), ntohl(entry.pathSize));

		if (entryPath == path) {
			if (m_file->tellg() + ntohl(entry.size) > fileSize) {
				throw CorruptDataException("Entry size is too large!");
			}

			std::vector<u8> data(ntohll(entry.size));
			m_file->read(data.data(), ntohll(entry.size));
			if (entry.checksum != Hash::crc32(data.data(), ntohll(entry.size))) {
				throw CorruptDataException("Asset " + path + " is corrupt!");
			}
			return data;
		}
		// Advance forward past data or data will be read as an entry header
		m_file->seekg(ntohll(entry.size), OS::File::Seek::Current);
	}
	throw NotFoundException("Asset " + path + " not found!");
}

void LTBundleAssetManager::saveAssetPure(std::string path, const u8 *data, size_t size, bool correctErrors) {
	if (m_file->getMode() & OS::File::FLAG_FILE_APPEND) {
		throw InvalidArgumentException("Cannot save to append mode file!");
	}
	if (!(m_file->getMode() & OS::File::FLAG_FILE_READ) || !(m_file->getMode() & OS::File::FLAG_FILE_WRITE)) {
		throw InvalidArgumentException("Cannot save without read/write mode file!");
	}
	m_file->seekp(0, OS::File::Seek::Begin);
	size_t fileSize = m_file->size();

	// Check if an existing header exists
	LTBundleHeader header;
	if (fileSize < sizeof(LTBundleHeader)) {
		header = {};
		m_file->seekp(sizeof(LTBundleHeader), OS::File::Seek::Begin);
	} else {
		m_file->read(&header, sizeof(LTBundleHeader));
		header.assetCount = ntohl(header.assetCount);
	}

	std::vector<LTBundleAssetEntry> entries;
	std::vector<std::string> paths;
	std::vector<std::vector<u8>> assetsData;

	if (header.magic == LTBUNDLE_MAGIC) {
		for (u32 i = 0; i < header.assetCount; i++) {
			bool errored = false;

			LTBundleAssetEntry entry;
			m_file->read(&entry, sizeof(LTBundleAssetEntry));

			std::string entryPath;
			if (m_file->tellg() + ntohl(entry.pathSize) > fileSize) {
				if (!correctErrors) {
					throw CorruptDataException("Entry path size too large!");
				}
				errored = true;
				m_file->seekg(ntohl(entry.pathSize), OS::File::Seek::Current);
			} else {
				entryPath.resize(ntohl(entry.pathSize));
				m_file->read(entryPath.data(), ntohl(entry.pathSize));
				if (entryPath == path) {
					errored = true;
				}
			}

			std::vector<u8> data(ntohll(entry.size));
			if (m_file->tellg() + ntohll(entry.size) > fileSize) {
				if (!correctErrors) {
					throw CorruptDataException("Entry size is too large!");
				}
				errored = true;
				m_file->seekg(ntohll(entry.size), OS::File::Seek::Current);
			} else {
				m_file->read(data.data(), ntohll(entry.size));
				if (entry.checksum != Hash::crc32(data.data(), ntohll(entry.size))) {
					if (!correctErrors) {
						throw CorruptDataException("Asset " + path + " is corrupt!");
					}
					errored = true;
				}
			}

			if (!errored) {
				entries.push_back(entry);
				paths.push_back(entryPath);
				assetsData.push_back(data);
			}
		}
	} else {
		header = {};
	}

	LTBundleAssetEntry entry;
	entry.pathSize = htonl(path.size());
	entry.size = htonll(size);
	entry.checksum = Hash::crc32(data, size);

	entries.push_back(entry);
	paths.push_back(path);

	std::vector<u8> assetData(size);
	memcpy(assetData.data(), data, size);
	assetsData.push_back(assetData);

	header.assetCount = htonl(entries.size());

	m_file->clear();
	m_file->seekp(0, OS::File::Seek::Begin);

	m_file->write(&header, sizeof(LTBundleHeader));
	for (u32 i = 0; i < ntohl(header.assetCount); i++) {
		m_file->write((u8 *)&entries[i], sizeof(LTBundleAssetEntry));
		m_file->write(paths[i].data(), ntohl(entries[i].pathSize));
		m_file->write(assetsData[i].data(), assetsData[i].size());
	}
}
