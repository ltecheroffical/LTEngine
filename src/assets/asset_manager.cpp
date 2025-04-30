#include <LTEngine/assets/asset_manager.hpp>


using namespace LTEngine;


const std::vector<u8> AssetManager::loadAsset(std::string path) {
	cacheEvictor();

	// Check if in cache
	if (m_cache.contains(path)) { return std::move(m_cache[path].data); }


	std::vector<u8> data;

	try {
		data = loadAssetPure(path);
	} catch (std::exception &e) {
		if (m_postProcessor == nullptr || !m_postProcessor->assetLoadFailed(path, &data)) { throw; }
	}
	if (m_postProcessor != nullptr) { m_postProcessor->postProcess(path, &data); }

	if (m_controller(path, data.data(), data.size())) {
		if (m_cache.contains(path)) {
			m_cache[path].lastAccessed = std::chrono::steady_clock::now().time_since_epoch().count();
		} else {
			m_cache[path] = CachedAsset{
				.path = path,
				.data = data,
				.lastAccessed = static_cast<u64>(std::chrono::steady_clock::now().time_since_epoch().count())
			};
		}
	}
	return std::move(data);
}

const std::vector<u8> AssetManager::loadAssetUncached(std::string path) {
	cacheEvictor();
	std::vector<u8> data;

	try {
		data = loadAssetPure(path);
	} catch (std::exception &e) {
		if (m_postProcessor == nullptr || !m_postProcessor->assetLoadFailed(path, &data)) { throw; }
	}
	if (m_postProcessor != nullptr) { m_postProcessor->postProcess(path, &data); }

	return std::move(data);
}

void AssetManager::saveAsset(std::string path, const u8 *data, size_t size) {
	cacheEvictor();
	std::vector<u8> processedData(size);
	for (u32 i = 0; i < size; i++) { processedData[i] = data[i]; }

	if (m_postProcessor != nullptr) { m_postProcessor->preProcess(path, &processedData); }

	if (m_controller(path, data, size)) {
		if (m_cache.contains(path)) {
			m_cache[path].lastAccessed = std::chrono::steady_clock::now().time_since_epoch().count();
		} else {
			m_cache[path] = CachedAsset{
				.path = path,
				.data = processedData,
				.lastAccessed = static_cast<u64>(std::chrono::steady_clock::now().time_since_epoch().count())
			};
		}
	}
	saveAssetPure(path, processedData.data(), processedData.size());
}


void AssetManager::cacheEvictor() {
	std::unordered_map<std::string, CachedAsset>::iterator it;
	for (it = m_cache.begin(); it != m_cache.end(); it++) {
		m_evictor(&it->second);
	}
}