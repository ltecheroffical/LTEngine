#ifndef _LTENGINE_LTBUNDLE_ASSET_MANAGER_HPP_
#define _LTENGINE_LTBUNDLE_ASSET_MANAGER_HPP_

#include <LTEngine/assets/asset_manager.hpp>


namespace LTEngine {
	class LTBundleAssetManager : public AssetManager {
	public:
		LTBundleAssetManager(std::string bundlePath);
		~LTBundleAssetManager() = default;

		const std::vector<u8> loadPure(const std::string &path) override;
		void saveAssetPure(const std::string &path, const u8 *data, size_t size) override;

	private:
		std::string m_bundlePath;
	};
} // namespace LTEngine

#endif
