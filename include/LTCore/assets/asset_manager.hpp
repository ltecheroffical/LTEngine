#ifndef _LTCORE_ASSET_MANAGER_HPP_
#define _LTCORE_ASSET_MANAGER_HPP_

#include <chrono>
#include <string>
#include <functional>
#include <unordered_map>
#include <vector>

#include <LTCore/common/data_size.h>
#include <LTCore/assets/asset_post_processor.hpp>

namespace LTCore {
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
	class LTCORE_API AssetManager {
	public:
		AssetManager() = default;
		virtual ~AssetManager() = default;

		// May throw InvalidDataException, NotFoundException, or std::runtime_error
		const std::vector<u8> loadAsset(std::string path);
		// May throw InvalidDataException, NotFoundException, or std::runtime_error
		const std::vector<u8> loadAssetUncached(std::string path);
		/* Loads an asset without caching or processing.
		 * May throw InvalidDataException, NotFoundException, or std::runtime_error
		 */
		virtual const std::vector<u8> loadAssetPure(std::string path) = 0;
		// May throw InvalidDataException, ConflictException, or std::runtime_error
		void saveAsset(std::string path, const u8 *data, size_t size);
		/* Saves an asset without caching or processing.
		 * May throw InvalidDataException, ConflictException, or std::runtime_error
		 */
		virtual void saveAssetPure(std::string path, const u8 *data, size_t size) = 0;

		// The controller decides if to cache
		void setCacheController(std::function<bool(std::string path, const u8 *data, size_t size)> controller) {
			m_controller = controller;
		}

		private: struct CachedAsset;
		public:
		// Cache eviction called every load and save
		void setCacheEvictor(std::function<bool(const CachedAsset *asset)> evictor) {
			m_evictor = evictor;
		}
		// Evicts cache when older than 10 seconds
		void resetCacheEvictor() {
			m_evictor = DEFAULT_EVICTOR;
		}

		// Default controller caches if asset is less than 16KB
		void resetCacheController() {
			m_controller = DEFAULT_CONTROLLER;
		}

		void clearCache() {
			m_cache.clear();
		}
		// Removes an asset from the cache
		void removeCachedAsset(std::string path) {
			m_cache.erase(path);
		}

		/**
		 * @brief Set the asset manager post processor.
		 *
		 * @details
		 * The asset manager post processor is used to process assets before saved. See `AssetManagerPostProcessor` for uses.
		 */
		void setPostProcessor(AssetManagerPostProcessor *postProcessor) {
			m_postProcessor = postProcessor;
		}


	private:
		struct CachedAsset {
			std::string path;
			std::vector<u8> data;
			u64 lastAccessed;
		};

		void cacheEvictor();

		const std::function<bool(std::string path, const u8 *data, size_t size)> DEFAULT_CONTROLLER = [](std::string path, const u8 *data, size_t size) {
			return size < LTCORE_KB(16);
		};
		
		const std::function<bool(const CachedAsset *asset)> DEFAULT_EVICTOR = [](const CachedAsset *asset) {
			return asset->lastAccessed > (std::chrono::steady_clock::now().time_since_epoch().count() + std::chrono::seconds(10).count());
		};

		AssetManagerPostProcessor *m_postProcessor = nullptr;

		std::function<bool(std::string path, const u8 *data, size_t size)> m_controller = DEFAULT_CONTROLLER;
		std::function<bool(const CachedAsset *asset)> m_evictor = DEFAULT_EVICTOR;

		std::unordered_map<std::string, CachedAsset> m_cache;
	};
} // namespace LTCore

#endif
