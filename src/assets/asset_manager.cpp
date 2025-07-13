#include <LTEngine/assets/asset_manager.hpp>


using namespace LTEngine;

const std::vector<u8> AssetManager::load_asset(std::string path) {
	_cache_evictor();

	// Check if in cache
	if (_cache.contains(path)) {
		return std::move(_cache[path].data);
	}


	std::vector<u8> data;

	try {
		data = load_asset_pure(path);
	} catch (std::exception &e) {
		if (_post_processor == nullptr || !_post_processor->asset_load_failed(path, &data)) {
			throw;
		}
	}
	if (_post_processor != nullptr) {
		_post_processor->post_process(path, &data);
	}

	if (_controller(path, data.data(), data.size())) {
		if (_cache.contains(path)) {
			_cache[path].last_accessed = std::chrono::steady_clock::now().time_since_epoch().count();
		} else {
			_cache[path] = CachedAsset{
			    .path = path,
			    .data = data,
			    .last_accessed = static_cast<u64>(std::chrono::steady_clock::now().time_since_epoch().count())};
			_used_cache_memory += data.size();
		}
	}
	return std::move(data);
}

const std::vector<u8> AssetManager::load_asset_uncached(std::string path) {
	_cache_evictor();
	std::vector<u8> data;

	try {
		data = load_asset_pure(path);
	} catch (std::exception &e) {
		if (_post_processor == nullptr || !_post_processor->asset_load_failed(path, &data)) {
			throw;
		}
	}
	if (_post_processor != nullptr) {
		_post_processor->post_process(path, &data);
	}

	return std::move(data);
}

void AssetManager::save_asset(std::string path, const u8 *data, size_t size) {
	_cache_evictor();
	std::vector<u8> processed_data(size);
	for (u32 i = 0; i < size; i++) {
		processed_data[i] = data[i];
	}

	if (_post_processor != nullptr) {
		_post_processor->pre_process(path, &processed_data);
	}

	if (_controller(path, data, size)) {
		if (_cache.contains(path)) {
			_cache[path].last_accessed = std::chrono::steady_clock::now().time_since_epoch().count();
		} else {
			_cache[path] = CachedAsset{
			    .path = path,
			    .data = processed_data,
			    .last_accessed = static_cast<u64>(std::chrono::steady_clock::now().time_since_epoch().count())};
			_used_cache_memory += processed_data.size();
		}
	}
	save_asset_pure(path, processed_data.data(), processed_data.size());
}

void AssetManager::_cache_evictor() {
	std::unordered_map<std::string, CachedAsset>::iterator it;
	for (it = _cache.begin(); it != _cache.end(); it++) {
		if (_evictor(&it->second, _used_cache_memory)) {
			_cache.erase(it);
			it = _cache.begin();
		}
	}
}
