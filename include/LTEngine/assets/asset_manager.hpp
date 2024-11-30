#ifndef _LTENGINE_ASSET_MANAGER_HPP_
#define _LTENGINE_ASSET_MANAGER_HPP_

#include <string>
#include <unordered_map>
#include <vector>

#include <LTEngine/assets/asset_post_processor.hpp>

#include <LTEngine/common/types/inttypes.h>


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
	class AssetManager {
	public:
		AssetManager() = default;
		virtual ~AssetManager() = default;

		const std::vector<u8> loadAsset(std::string path);
		/**
		 * @brief Load asset without caching or processing.
		 */
		virtual const std::vector<u8> loadAssetPure(std::string path) = 0;
		void saveAsset(std::string path, const u8 *data, size_t size);
		/**
		 * @brief Save asset without caching or processing.
		 */
		virtual void saveAssetPure(std::string path, const u8 *data, size_t size) = 0;

		void clearCache() { m_cache.clear(); }

		void removeCachedAsset(std::string path) { m_cache.erase(path); }

		/**
		 * @brief Set the asset manager post processor.
		 *
		 * @details
		 * The asset manager post processor is used to process assets before saved. See `AssetManagerPostProcessor` for uses.
		 */
		void setPostProcessor(AssetManagerPostProcessor *postProcessor) { m_postProcessor = postProcessor; }

	private:
		AssetManagerPostProcessor *m_postProcessor = nullptr;

		std::unordered_map<std::string, std::vector<u8>> m_cache;
	};
} // namespace LTEngine

#endif
