#pragma once

#include <LTEngine/assets/asset_manager.hpp>


namespace LTEngine {
    class DirectoryAssetManager : public AssetManager {
    public:
        DirectoryAssetManager(std::string directory);
        ~DirectoryAssetManager() = default;

        const std::vector<u8> loadPure(const std::string &path) override;
        void saveAssetPure(const std::string &path, const u8 *data, u32 size) override;

    private:
        std::string m_directory;
    };
}
