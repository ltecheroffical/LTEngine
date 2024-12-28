#ifndef _LTENGINE_LTBUNDLE_ASSET_MANAGER_HPP_
#define _LTENGINE_LTBUNDLE_ASSET_MANAGER_HPP_

#include <LTEngine/os/file.hpp>

#include <LTEngine/assets/asset_manager.hpp>


namespace LTEngine {
	class LTENGINE_API LTBundleAssetManager : public AssetManager {
	public:
		LTBundleAssetManager(LTEngine::OS::File *file);
		~LTBundleAssetManager() = default;

		const std::vector<u8> loadAssetPure(std::string path) override;
		void saveAssetPure(std::string path, const u8 *data, size_t size) override;

	private:
		LTEngine::OS::File *m_file;
	};
} // namespace LTEngine

#endif
