#include <fstream>

#include <LTEngine/hash/crc32.hpp>

#include <LTEngine/assets/ltbundle_asset_manager.hpp>


using namespace LTEngine;


const u32 LTBUNDLE_VERSION = 1;
const char LTBUNDLE_MAGIC[4] = { 'L', 'T', 'B', 'N' };


#pragma pack(1)
struct LTBundleHeader {
    char magic[4] = { LTBUNDLE_MAGIC[0], LTBUNDLE_MAGIC[1], LTBUNDLE_MAGIC[2], LTBUNDLE_MAGIC[3] };
    u32 version = LTBUNDLE_VERSION;

    u32 assetCount = 0;
};

struct LTBundleAssetEntry {
    u32 pathSize;
    u32 size;
    u32 checksum;
};
#pragma pack()


LTBundleAssetManager::LTBundleAssetManager(std::string bundlePath) {
    m_bundlePath = bundlePath;
}


const std::vector<u8> LTBundleAssetManager::loadPure(const std::string &path) {
    std::ifstream file(m_bundlePath, std::ios::binary);
    file.seekg(0, std::ios_base::end);
    u32 fileSize = file.tellg();
    file.seekg(0, std::ios_base::beg);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open bundle file!");
    }

    if (fileSize < sizeof(LTBundleHeader)) {
        throw std::runtime_error("Bundle file is corrupt or not a LTBundle file!");
    }

    LTBundleHeader header;
    file.read((char *)&header, sizeof(LTBundleHeader));

    if (header.magic[0] != 'L' || header.magic[1] != 'T' || header.magic[2] != 'B' || header.magic[3] != 'N') {
        throw std::runtime_error("Bundle file is corrupt or not a LTBundle file!");
    }

    if (header.version != LTBUNDLE_VERSION) {
        throw std::runtime_error("Invalid LTBundle version!");
    }

    for (u32 i = 0; i < header.assetCount; i++) {
        LTBundleAssetEntry entry;
        file.read((char *)&entry, sizeof(LTBundleAssetEntry));

        if (entry.pathSize + entry.size > fileSize) {
            throw std::runtime_error("Bundle file is corrupt or not a LTBundle file!");
        }
        
        std::string entry_path;
        entry_path.resize(entry.pathSize);

        file.read((char *)entry_path.data(), entry.pathSize);

        if (entry_path == path) {
            std::vector<u8> data(entry.size);
            file.read((char *)data.data(), entry.size);
            if (entry.checksum != Hash::crc32(data.data(), entry.size)) {
                throw std::runtime_error("Asset is corrupt!");
            }
            return data;
        } else {
            // Advance forward past data or data will be read as an entry header
            file.seekg(entry.size, std::ios_base::cur);
        }
    }
    throw std::runtime_error("Asset not found in bundle!");
}

void LTBundleAssetManager::saveAssetPure(const std::string &path, const u8 *data, u32 size) {
    // Check if an existing header exists
    std::fstream file(m_bundlePath, std::ios::binary | std::ios::in | std::ios::out);
    if (!file.is_open()) {
        // Try creating it first?
        file = std::fstream(m_bundlePath, std::ios::binary | std::ios::out);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open bundle file!");
        }

        // Replace with actual fstream
        file.close();
        file = std::fstream(m_bundlePath, std::ios::binary | std::ios::in | std::ios::out);
    }

    file.seekg(0, std::ios_base::end);
    u32 fileSize = file.tellg();
    file.seekg(0, std::ios_base::beg);

    LTBundleHeader header;
    if (fileSize < sizeof(LTBundleHeader)) {
        header = {};
        file.seekp(sizeof(LTBundleHeader), std::ios_base::beg);
    } else {
        file.read((char *)&header, sizeof(LTBundleHeader));
    }

    if (header.magic[0] != 'L' || header.magic[1] != 'T' || header.magic[2] != 'B' || header.magic[3] != 'N') {
        header = {};
        header.assetCount = 0;
    }


    std::vector<LTBundleAssetEntry> entries(header.assetCount + 1);
    std::vector<std::string> paths(header.assetCount + 1);
    std::vector<std::vector<u8>> assetsData(header.assetCount + 1);
    for (u32 i = 0; i < header.assetCount; i++) {
        file.read((char *)&entries[i], sizeof(LTBundleAssetEntry));
        paths[i].resize(entries[i].pathSize);
        file.read(paths[i].data(), entries[i].pathSize);
        if (paths[i] == path) {
            file.close();
            throw std::runtime_error("Asset already exists in bundle!");
        }
        std::vector<u8> assetData(entries[i].size);
        file.read((char *)assetData.data(), entries[i].size);
        assetsData[i] = assetData;
    }
    

    entries[header.assetCount].pathSize = path.size();
    entries[header.assetCount].size = size;
    entries[header.assetCount].checksum = Hash::crc32(data, size);

    paths[header.assetCount] = path;

    assetsData[header.assetCount].resize(size);
    for (u32 i = 0; i < size; i++) {
        assetsData[header.assetCount][i] = data[i];
    }
    header.assetCount++;

    
    // Rewrite file
    file.seekp(0, std::ios_base::beg);

    file.write((char *)&header, sizeof(LTBundleHeader));
    for (u32 i = 0; i < header.assetCount; i++) {
        file.write((char *)&entries[i], sizeof(LTBundleAssetEntry));
        file.write(paths[i].data(), entries[i].pathSize);
        file.write((char *)assetsData[i].data(), assetsData[i].size());
    }
    file.close();
}
