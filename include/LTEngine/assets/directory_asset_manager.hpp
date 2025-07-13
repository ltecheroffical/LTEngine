#ifndef _LTENGINE_DIRECTORY_ASSET_MANAGER_HPP_
#define _LTENGINE_DIRECTORY_ASSET_MANAGER_HPP_

#include <string>
#include <unordered_map>

#include <LTEngine/os/fstream_file.hpp>

#include <LTEngine/assets/asset_manager.hpp>

namespace LTEngine {
class LTENGINE_API DirectoryAssetManager : public AssetManager {
	DirectoryAssetManager(std::string directory);
	~DirectoryAssetManager() = default;

	const std::vector<u8> _load_asset_pure(std::string path) ;
	void _save_asset_pure(std::string path, const u8 *data, size_t size, bool) ;

  private:
	std::string _directory;
	std::unordered_map<std::string, OS::FStreamFile> _files;
};
} // namespace LTEngine

#endif
