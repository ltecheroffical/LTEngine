#include <filesystem>

#include <LTEngine/assets/directory_asset_manager.hpp>


using namespace LTEngine;

DirectoryAssetManager::DirectoryAssetManager(std::string directory)
    : _directory(directory) {
}

const std::vector<u8> DirectoryAssetManager::_load_asset_pure(std::string path) {
	if (!_files.contains(path)) {
		_files[path].open((std::filesystem::path(_directory) / std::filesystem::path(path)).c_str(), OS::File::FLAG_FILE_READ | OS::File::FLAG_FILE_WRITE);
	}
	_files[path].seekp(0, OS::File::Seek::BEGIN);

	std::vector<u8> data(_files[path].size());
	_files[path].read(data.data(), data.size());
	return data;
}

void DirectoryAssetManager::_save_asset_pure(std::string path, const u8 *data, size_t size, bool) {
	if (!_files.contains(path)) {
		_files[path].open((std::filesystem::path(_directory) / std::filesystem::path(path)).c_str(),
		                   OS::File::FLAG_FILE_READ | OS::File::FLAG_FILE_WRITE | OS::File::FLAG_FILE_CREATE);
	}
	_files[path].seekp(0, OS::File::Seek::BEGIN);
	_files[path].write(data, size);
}
