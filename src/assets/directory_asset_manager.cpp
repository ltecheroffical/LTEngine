#include <fstream>

#include <LTEngine/assets/directory_asset_manager.hpp>


using namespace LTEngine;


DirectoryAssetManager::DirectoryAssetManager(std::string directory) {
    m_directory = directory;
}


const std::vector<u8> DirectoryAssetManager::loadPure(const std::string &path) {
    std::ifstream file(m_directory + path, std::ios::binary);
    std::vector<u8> data((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
    return data;
}

void DirectoryAssetManager::saveAssetPure(const std::string &path, const std::vector<u8> &data) {
    std::ofstream file(m_directory + path, std::ios::binary);
    file.write((char *)data.data(), data.size());
}
