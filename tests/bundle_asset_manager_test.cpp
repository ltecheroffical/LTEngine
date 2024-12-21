#define LTENGINE_GLOBAL_BASIC_TYPES

#include <acutest.h>

#include <LTEngine/os/fstream_file.hpp>
#include <LTEngine/os/mem_file.hpp>

#include <LTEngine/assets/ltbundle_asset_manager.hpp>


// Thanks XXD! (The command line utility for dumping binary files)
// Data stored:
//  (All in big endian except asset data)
//  Version: 1
//  Asset Count: 2
//  Asset 1:
//      Name: "test_asset1"
//      Data Size: 32 bytes
//      Data: [See testData1]
//  Asset 2:
//      Name: "test_asset2"
//      Data Size: 32 bytes
//      Data: [See testData2]
const u8 testAssetData[] = {0x4c, 0x54, 0x42, 0x4e, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x2e, 0x34, 0x6b, 0xe8, 0x74, 0x65, 0x73, 0x74, 0x5f, 0x61,
                            0x73, 0x73, 0x65, 0x74, 0x31, 0x35, 0x0d, 0xe7, 0x4b, 0xa0, 0xf1, 0xc9, 0x45, 0x46, 0x8f, 0x99,
                            0xeb, 0xab, 0x2d, 0xc2, 0xe1, 0x72, 0x40, 0x12, 0xf7, 0x82, 0x9a, 0x78, 0xcd, 0x5d, 0x65, 0x33,
                            0xea, 0x67, 0x50, 0xc3, 0xc4, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x20, 0xb7, 0x17, 0x6a, 0x0f, 0x74, 0x65, 0x73, 0x74, 0x5f, 0x61, 0x73, 0x73, 0x65, 0x74, 0x32,
                            0xbd, 0x3e, 0x63, 0x9a, 0xb3, 0xe8, 0xb4, 0xaf, 0x46, 0xfc, 0xd6, 0x02, 0xeb, 0x72, 0x9f, 0x78,
                            0x5d, 0xa0, 0x21, 0x0f, 0x3b, 0x18, 0xc7, 0xb9, 0x1a, 0xa7, 0xd1, 0x3c, 0x34, 0x73, 0xcc, 0x0e};


void test_bundle_asset_manager_writing() {
	LTEngine::OS::MemFile memFile(LTEngine::OS::File::FLAG_FILE_READ | LTEngine::OS::File::FILE_WRITE);
	LTEngine::LTBundleAssetManager manager(&memFile);

	const std::vector<u8> testData1 = {41,  40, 69,  124, 186, 7,  173, 185, 205, 195, 236, 8,  4,   210, 86,  29,
	                                   220, 61, 193, 230, 157, 72, 246, 249, 213, 155, 182, 52, 112, 36,  214, 147};
	const std::vector<u8> testData2 = {181, 148, 14,  21, 75,  52, 244, 48, 55,  110, 88, 229, 214, 246, 215, 231,
	                                   60,  34,  240, 11, 226, 69, 66,  68, 135, 239, 31, 46,  2,   74,  24,  42};

	manager.saveAsset("test_asset1", testData1.data(), testData1.size());
	manager.saveAsset("test_asset2", testData2.data(), testData2.size());

	manager.clearCache();

	TEST_CHECK(manager.loadAsset("test_asset1") == testData1);
	TEST_CHECK(manager.loadAsset("test_asset2") == testData2);
}

void test_bundle_asset_manager_reading() {
#ifdef LTENGINE_COMPILER_DATA_COMPATIBILITY_ISSUE
	// For the test asset data, it's been saved where data compatibility is expected
	// Without it, it's likely the test will fail
	TEST_SKIP("Data compatibility issue");
#endif

	LTEngine::OS::MemFile file(testAssetData, sizeof(testAssetData), LTEngine::OS::File::FLAG_FILE_READ);
	LTEngine::LTBundleAssetManager manager(&file);

	std::vector<u8> testData1 = {53,  13, 231, 75,  160, 241, 201, 69,  70, 143, 153, 235, 171, 45, 194, 225,
	                             114, 64, 18,  247, 130, 154, 120, 205, 93, 101, 51,  234, 103, 80, 195, 196};
	std::vector<u8> testData2 = {189, 62,  99, 154, 179, 232, 180, 175, 70, 252, 214, 2,  235, 114, 159, 120,
	                             93,  160, 33, 15,  59,  24,  199, 185, 26, 167, 209, 60, 52,  115, 204, 14};

	/* Code used to generate the test file
	manager.saveAssetPure("test_asset1", testData1.data(), testData1.size());
	manager.saveAssetPure("test_asset2", testData2.data(), testData2.size());
	*/

	TEST_CHECK(manager.loadAsset("test_asset1") == testData1);
	TEST_CHECK(manager.loadAsset("test_asset2") == testData2);
}

void test_bundle_asset_manager_save_already_exists() {
#ifdef LTENGINE_COMPILER_DATA_COMPATIBILITY_ISSUE
	// For the test asset data, it's been saved where data compatibility is expected
	// Without it, it's likely the test will fail
	TEST_SKIP("Data compatibility issue");
#endif

	LTEngine::OS::MemFile file(testAssetData, sizeof(testAssetData),
	                           LTEngine::OS::File::FILE_WRITE | LTEngine::OS::File::FLAG_FILE_READ);
	LTEngine::LTBundleAssetManager manager(&file);
	const u8 testData[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
	TEST_EXCEPTION(manager.saveAsset("test_asset1", testData, sizeof(testData)), std::runtime_error);
}

void test_bundle_asset_manger_load_non_existent_asset() {
#ifdef LTENGINE_COMPILER_DATA_COMPATIBILITY_ISSUE
	// For the test asset data, it's been saved where data compatibility is expected
	// Without it, it's likely the test will fail
	TEST_SKIP("Data compatibility issue");
#endif

	LTEngine::OS::MemFile file(&testAssetData, sizeof(testAssetData), LTEngine::OS::File::FLAG_FILE_READ);
	LTEngine::LTBundleAssetManager manager(&file);
	TEST_EXCEPTION(manager.loadAsset("non_existent_asset"), std::runtime_error);
}


TEST_LIST = {
    // Should be able to write without error
    {"test_bundle_asset_manager_writing", test_bundle_asset_manager_writing},
    // Should be able to read without error with matching data
    {"test_bundle_asset_manager_reading", test_bundle_asset_manager_reading},

    // Should throw an exception when trying to save an asset that already exists
    {"test_bundle_asset_manager_save_already_exists", test_bundle_asset_manager_save_already_exists},
    // Should throw an error when trying to load a non-existent asset
    {"test_bundle_asset_manger_load_non_existent_asset", test_bundle_asset_manger_load_non_existent_asset},

    {NULL, NULL}};
