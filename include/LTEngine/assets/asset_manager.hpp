#ifndef _LTENGINE_ASSET_MANAGER_HPP_
#define _LTENGINE_ASSET_MANAGER_HPP_

#include <string>
#include <unordered_map>
#include <vector>

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

		// May throw InvalidDataException, NotFoundException, or std::runtime_error
		const std::vector<u8> loadAsset(std::string path);
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
		AssetManagerPostProcessor *m_postProcessor = nullptr;

		std::unordered_map<std::string, std::vector<u8>> m_cache;
	};
} // namespace LTEngine

#endif
