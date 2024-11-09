#include <LTEngine/assets/asset_manager.hpp>


using namespace LTEngine;


const std::vector<u8> AssetManager::load(const std::string &path) {
    // Check if in cache
    if (m_cache.contains(path)) {
        return std::move(m_cache[path]);
    }

    std::vector<u8> data = loadPure(path);
   
    if (m_postProcessor != nullptr) {
        m_postProcessor->preProcess(data);
    }

    m_cache[path] = data;
    return std::move(data);
}

void AssetManager::saveAsset(const std::string &path, const std::vector<u8> &data) {
    std::vector<u8> processedData = data;
    
    if (m_postProcessor != nullptr) {
        m_postProcessor->preProcess(processedData);
    }

    m_cache[path] = processedData;
    saveAssetPure(path, processedData);
}
