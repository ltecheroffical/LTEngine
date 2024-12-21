#include <LTEngine/assets/directory_asset_manager.hpp>


using namespace LTEngine;


DirectoryAssetManager::DirectoryAssetManager(std::string directory) : m_directory(directory) {}


const std::vector<u8> DirectoryAssetManager::loadAssetPure(std::string path) {
	if (!m_files.contains(path)) {
		m_files[path].open((m_directory + "/" + path).c_str(), OS::File::FLAG_FILE_READ | OS::File::FLAG_FILE_WRITE);
	}
	m_files[path].seekp(0, OS::File::Seek::Begin);

	std::vector<u8> data(m_files[path].size());
	m_files[path].read(data.data(), data.size());
	return data;
}

void DirectoryAssetManager::saveAssetPure(std::string path, const u8 *data, size_t size) {
	if (!m_files.contains(path)) {
		m_files[path].open((m_directory + "/" + path).c_str(),
		                   OS::File::FLAG_FILE_READ | OS::File::FLAG_FILE_WRITE | OS::File::FLAG_FILE_CREATE);
	}
	m_files[path].seekp(0, OS::File::Seek::Begin);
	m_files[path].write(data, size);
}
