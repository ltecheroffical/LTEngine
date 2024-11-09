#include <LTEngine/assets/ltbundle_asset_manager.hpp>

#include <acutest.h>


#ifdef _WIN32
#define TEMP_DIR (char*)"."
#else
#define TEMP_DIR (char*)"/tmp"
#endif


void test_bundle_asset_manager_writing() {
    LTEngine::LTBundleAssetManager manager(TEMP_DIR "/bundle_asset_manager_test");
   
    std::vector<u8> testData1 = {41, 40, 69, 124, 186, 7, 173, 185, 205, 195, 236, 8, 4, 210, 86, 29, 220, 61, 193, 230, 157, 72, 246, 249, 213, 155, 182, 52, 112, 36, 214, 147};
    std::vector<u8> testData2 = {181, 148, 14, 21, 75, 52, 244, 48, 55, 110, 88, 229, 214, 246, 215, 231, 60, 34, 240, 11, 226, 69, 66, 68, 135, 239, 31, 46, 2, 74, 24, 42};

    manager.saveAssetPure("test_asset1", testData1);
    manager.saveAssetPure("test_asset2", testData2);

    manager.clearCache();

    TEST_CHECK(manager.loadPure("test_asset1") == testData1);
    TEST_CHECK(manager.loadPure("test_asset2") == testData2);

    // Delete the test file
    std::remove(TEMP_DIR "/bundle_asset_manager_test");
}

void test_bundle_asset_manager_reading() {
    LTEngine::LTBundleAssetManager manager(RESOURCES_PATH "/ltbundle_test.bin");

    std::vector<u8> testData1 = {53, 13, 231, 75, 160, 241, 201, 69, 70, 143, 153, 235, 171, 45, 194, 225, 114, 64, 18, 247, 130, 154, 120, 205, 93, 101, 51, 234, 103, 80, 195, 196};
    std::vector<u8> testData2 = {189, 62, 99, 154, 179, 232, 180, 175, 70, 252, 214, 2, 235, 114, 159, 120, 93, 160, 33, 15, 59, 24, 199, 185, 26, 167, 209, 60, 52, 115, 204, 14};

    /* Code used to generate the test file
    manager.saveAssetPure("test_asset1", testData1);
    manager.saveAssetPure("test_asset2", testData2);
    */

    TEST_CHECK(manager.loadPure("test_asset1") == testData1);
    TEST_CHECK(manager.loadPure("test_asset2") == testData2);
}


TEST_LIST = {
    { "test_bundle_asset_manager_writing", test_bundle_asset_manager_writing },
    { "test_bundle_asset_manager_reading", test_bundle_asset_manager_reading },

    { NULL, NULL }
};
