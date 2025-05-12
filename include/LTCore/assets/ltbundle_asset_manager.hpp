#ifndef _LTCORE_LTBUNDLE_ASSET_MANAGER_HPP_
#define _LTCORE_LTBUNDLE_ASSET_MANAGER_HPP_

#include <LTCore/os/file.hpp>

#include <LTCore/assets/asset_manager.hpp>


namespace LTCore {
	class LTCORE_API LTBundleAssetManager : public AssetManager {
	public:
		LTBundleAssetManager(LTCore::OS::File *file);
		~LTBundleAssetManager() = default;

		const std::vector<u8> loadAssetPure(std::string path) override;
		void saveAssetPure(std::string path, const u8 *data, size_t size) override;

	private:
		LTCore::OS::File *m_file;
	};
} // namespace LTCore

#endif
