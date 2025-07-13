#ifndef _LTENGINE_ASSET_MANAGER_HPP_
#define _LTENGINE_ASSET_MANAGER_HPP_

#include <chrono>
#include <string>
#include <functional>
#include <unordered_map>
#include <vector>

#include <LTEngine/common/data_size.h>
#include <LTEngine/assets/asset_post_processor.hpp>

namespace LTEngine {
/**
 * @brief A simple asset manager.
 *
 * @details
 * The goal is to make loading, saving and caching assets easier.
 * Some benefits of a manager like this are as follows:
 *  - It is easy to cache assets.
 *  - You can swap the asset manager for debug and release builds. (e.g DirectoryAssetManager in Debug and BundleAssetManager in
 * Release)
 *  - It's easier to encrypt, compress, download from server and more with a manager like this.
 * Release)
 */


class LTENGINE_API AssetManager {
  public:
	AssetManager() = default;
	virtual ~AssetManager() = default;

	struct CachedAsset {
		std::string path;
		std::vector<u8> data;
		u64 last_accessed;
	};

	typedef std::function<bool(std::string path, const u8 *data, size_t size)> CacheControllerFunction;
	typedef std::function<bool(const CachedAsset *asset, size_t used_cache_memory)> CacheEvictorFunction;

	// May throw InvalidDataException, NotFoundException, or std::runtime_error
	const std::vector<u8> load_asset(std::string path);
	// May throw InvalidDataException, NotFoundException, or std::runtime_error
	const std::vector<u8> load_asset_uncached(std::string path);
	/* Loads an asset without caching or processing.
	 * May throw InvalidDataException, NotFoundException, or std::runtime_error
	 */
	virtual const std::vector<u8> load_asset_pure(std::string path) = 0;
	// May throw InvalidDataException, ConflictException, or std::runtime_error
	void save_asset(std::string path, const u8 *data, size_t size);
	/* Saves an asset without caching or processing.
	 * May throw InvalidDataException, or std::runtime_error
	 * On path conflict, replace asset. (In place not required)
	 */
	virtual void save_asset_pure(std::string path, const u8 *data, size_t size, bool correct_errors = false) = 0;

	// The controller decides if to cache
	void set_cache_controller(CacheControllerFunction controller) {
		_controller = controller;
	}

	// Cache eviction called every load and save
	void set_cache_evictor(CacheEvictorFunction evictor) {
		_evictor = evictor;
	}

	// Evicts cache when older than 10 seconds
	void reset_cache_evictor() {
		_evictor = _default_evictor;
	}

	// Default controller caches if asset is less than 16KB
	void reset_cache_controller() {
		_controller = _default_controller;
	}

	void clear_cache() {
		_cache.clear();
	}

	// Removes an asset from the cache
	void remove_cached_asset(std::string path) {
		_cache.erase(path);
	}

	/**
	 * @brief Set the asset manager post processor.
	 *
	 * @details
	 * The asset manager post processor is used to process assets before saved. See `AssetManagerPostProcessor` for uses.
	 */
	void set_post_processor(AssetManagerPostProcessor *post_processor) {
		_post_processor = post_processor;
	}


  private:
	void _cache_evictor();

	const CacheControllerFunction _default_controller = [](std::string path, const u8 *data, size_t size) {
		return size < LTENGINE_KB(16);
	};

	const CacheEvictorFunction _default_evictor = [](const CachedAsset *asset, size_t used_cache_memory) {
		return asset->last_accessed > (std::chrono::steady_clock::now().time_since_epoch().count() + std::chrono::seconds(10).count()) || used_cache_memory > LTENGINE_MB(256);
	};

	AssetManagerPostProcessor *_post_processor = nullptr;

	std::function<bool(std::string path, const u8 *data, size_t size)> _controller = _default_controller;
	std::function<bool(const CachedAsset *asset, size_t used_cache_memory)> _evictor = _default_evictor;
	size_t _used_cache_memory = 0;

	std::unordered_map<std::string, CachedAsset> _cache;
};
} // namespace LTEngine

#endif
