#ifndef _LTENGINE_LTBUNDLE_ASSET_MANAGER_HPP_
#define _LTENGINE_LTBUNDLE_ASSET_MANAGER_HPP_

#include <LTEngine/os/file.hpp>

#include <LTEngine/assets/asset_manager.hpp>

namespace LTEngine {
class LTENGINE_API LTBundleAssetManager : public AssetManager {
  public:
	LTBundleAssetManager(LTEngine::OS::File *file);
	~LTBundleAssetManager() = default;

	const std::vector<u8> load_asset_pure(std::string path) ;
	void save_asset_pure(std::string path, const u8 *data, size_t size, bool correct_errors) ;

  private:
	LTEngine::OS::File *_file;
};
} // namespace LTEngine

#endif
