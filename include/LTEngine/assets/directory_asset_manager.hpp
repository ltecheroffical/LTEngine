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

		const std::vector<u8> loadAssetPure(std::string path) override;
		void saveAssetPure(std::string path, const u8 *data, size_t size) override;

	private:
		std::string m_directory;
		std::unordered_map<std::string, OS::FStreamFile> m_files;
	};
} // namespace LTEngine

#endif
