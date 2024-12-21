#ifdef _WIN32
#include <Winsock2.h>
#else
#include <arpa/inet.h>
#endif

#include <LTEngine/common/compiler_utils.h>

#include <LTEngine/hash.hpp>

#include <LTEngine/assets/ltbundle_asset_manager.hpp>


using namespace LTEngine;


const u16 LTBUNDLE_VERSION = 1;
const char LTBUNDLE_MAGIC[4] = {'L', 'T', 'B', 'N'};


LTENGINE_PACK_START() struct LTBundleHeader {
	char magic[4] = {LTBUNDLE_MAGIC[0], LTBUNDLE_MAGIC[1], LTBUNDLE_MAGIC[2], LTBUNDLE_MAGIC[3]};
	u16 version = LTBUNDLE_VERSION;

	u32 assetCount = 0;
} LTENGINE_PACK_END();

LTENGINE_PACK_START() struct LTBundleAssetEntry {
	u32 pathSize;
	u64 size;
	u32 checksum;
} LTENGINE_PACK_END();


LTBundleAssetManager::LTBundleAssetManager(LTEngine::OS::File *file) : m_file(file) {}


const std::vector<u8> LTBundleAssetManager::loadAssetPure(std::string path) {
	if (!(m_file->getMode() & OS::File::FILE_READ)) { throw std::runtime_error("Cannot load without read mode file!"); }

	m_file->seekp(0, OS::File::Seek::Begin);
	size_t fileSize = m_file->size();

	if (fileSize < sizeof(LTBundleHeader)) { throw std::runtime_error("Bundle file is corrupt or not a LTBundle file! (Header)"); }

	LTBundleHeader header;
	m_file->read(&header, sizeof(LTBundleHeader));

	if (header.magic[0] != 'L' || header.magic[1] != 'T' || header.magic[2] != 'B' || header.magic[3] != 'N') {
		throw std::runtime_error("Bundle file is corrupt or not a LTBundle file!");
	}

	if (ntohs(header.version) != LTBUNDLE_VERSION) { throw std::runtime_error("Invalid LTBundle version!"); }

	for (u32 i = 0; i < ntohl(header.assetCount); i++) {
		LTBundleAssetEntry entry;
		m_file->read(&entry, sizeof(LTBundleAssetEntry));

		u32 entrySize = (ntohl(((entry.size >> 32) & 0xFFFFFFFF)) | (ntohl(entry.size) & 0xFFFFFFFF));
		if (ntohl(entry.pathSize) + entrySize > fileSize) {
			throw std::runtime_error("Bundle file is corrupt or not a LTBundle file! (Entry path size too large! " +
			                         std::to_string(ntohl(entry.pathSize)) + " + " + std::to_string(entrySize) + " > " +
			                         std::to_string(fileSize) + ")");
		}

		std::string entry_path;
		entry_path.resize(ntohl(entry.pathSize));

		m_file->read(entry_path.data(), ntohl(entry.pathSize));

		if (entry_path == path) {
			std::vector<u8> data(ntohl(((entry.size >> 32) & 0xFFFFFFFF)) | (ntohl(entry.size) & 0xFFFFFFFF));
			m_file->read(data.data(), ntohl(((entry.size >> 32) & 0xFFFFFFFF)) | (entry.size & 0xFFFFFFFF));
			if (entry.checksum != Hash::crc32(data.data(), ntohl((entry.size >> 32) & 0xFFFFFFFF))) {
				throw std::runtime_error("Asset " + path + " is corrupt!");
			}
			return data;
		}
		// Advance forward past data or data will be read as an entry header
		m_file->seekg(ntohl(((entry.size >> 32) & 0xFFFFFFFF)) | (ntohl(entry.size) & 0xFFFFFFFF), OS::File::Seek::Current);
	}
	throw std::runtime_error("Asset not found in bundle!");
}

void LTBundleAssetManager::saveAssetPure(std::string path, const u8 *data, size_t size) {
	if (m_file->getMode() & OS::File::FILE_APPEND) { throw std::runtime_error("Cannot save with append mode file!"); }
	if (!(m_file->getMode() & OS::File::FILE_READ) || !(m_file->getMode() & OS::File::FILE_WRITE)) {
		throw std::runtime_error("Cannot save without read AND write mode file!");
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
		header.version = ntohs(header.version);
		header.assetCount = ntohl(header.assetCount);
	}

	if (header.magic[0] != 'L' || header.magic[1] != 'T' || header.magic[2] != 'B' || header.magic[3] != 'N') {
		header = {};
		header.assetCount = 0;
	}


	std::vector<LTBundleAssetEntry> entries(header.assetCount + 1);
	std::vector<std::string> paths(header.assetCount + 1);
	std::vector<std::vector<u8>> assetsData(header.assetCount + 1);
	for (u32 i = 0; i < header.assetCount; i++) {
		m_file->read(&entries[i], sizeof(LTBundleAssetEntry));
		paths[i].resize(ntohl(entries[i].pathSize));
		m_file->read(paths[i].data(), ntohl(entries[i].pathSize));
		if (paths[i] == path) { throw std::runtime_error("Asset already exists in bundle!"); }
		std::vector<u8> assetData((u64)ntohl(entries[i].size & 0xFFFFFFFF) << 32 | ntohl((entries[i].size >> 32) & 0xFFFFFFFF));
		m_file->read(assetData.data(), ntohl((entries[i].size >> 32) & 0xFFFFFFFF) | ntohl(entries[i].size & 0xFFFFFFFF));
		assetsData[i] = assetData;
	}


	entries[header.assetCount].pathSize = htonl(path.size());
	entries[header.assetCount].size = (u64)htonl(size & 0xFFFFFFFF) << 32 | htonl((size >> 32) & 0xFFFFFFFF);
	entries[header.assetCount].checksum = Hash::crc32(data, size);

	paths[header.assetCount] = path;

	assetsData[header.assetCount].resize(size);
	for (u32 i = 0; i < size; i++) { assetsData[header.assetCount][i] = data[i]; }
	header.assetCount++;


	// Rewrite file
	m_file->seekp(0, OS::File::Seek::Begin);

	header.version = htons(header.version);
	header.assetCount = htonl(header.assetCount);

	m_file->write(&header, sizeof(LTBundleHeader));
	for (u32 i = 0; i < ntohl(header.assetCount); i++) {
		m_file->write((char *)&entries[i], sizeof(LTBundleAssetEntry));
		m_file->write(paths[i].data(), ntohl(entries[i].pathSize));
		m_file->write((char *)assetsData[i].data(), assetsData[i].size());
	}
}
