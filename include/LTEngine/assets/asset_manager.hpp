#ifndef _LTENGINE_ASSET_MANAGER_HPP_
#define _LTENGINE_ASSET_MANAGER_HPP_

#include <string>
#include <unordered_map>
#include <vector>

#include <LTEngine/assets/asset_post_processor.hpp>

#include <LTEngine/common/types/inttypes.h>


namespace LTEngine {
	class AssetManager {
	public:
		AssetManager() = default;
		virtual ~AssetManager() = default;

		const std::vector<u8> load(const std::string &path);
		virtual const std::vector<u8> loadPure(const std::string &path) = 0;
		void saveAsset(const std::string &path, const u8 *data, u32 size);
		virtual void saveAssetPure(const std::string &path, const u8 *data, u32 size) = 0;

		void clearCache() { m_cache.clear(); }

		void removeCachedAsset(const std::string &path) { m_cache.erase(path); }

		void setPostProcessor(AssetManagerPostProcessor *postProcessor) { m_postProcessor = postProcessor; }

	private:
		AssetManagerPostProcessor *m_postProcessor = nullptr;

		std::unordered_map<std::string, std::vector<u8>> m_cache;
	};
} // namespace LTEngine

#endif
