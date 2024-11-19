#include <cstring>

#include <acutest.h>

#include <LTEngine/hash.hpp>


void test_crc32() {
	u8 data[] = {0xBF, 0x60, 0xCB, 0xCF, 0xEA, 0xAB, 0xE9, 0x27, 0xB5, 0xD0, 0x19, 0xA1, 0xD0, 0x51, 0x95, 0x8F};
	const u32 expected = 0x0126BFBB;
	u32 output = LTEngine::Hash::crc32(data, sizeof(data));

	TEST_CHECK(output == expected);
	TEST_DUMP("Expected", &expected, sizeof(expected));
	TEST_DUMP("Got", &output, sizeof(output));
}

void test_md5() {
	u8 data[] = {0x08, 0xEE, 0x22, 0xBA, 0x2E, 0x89, 0x95, 0x75, 0x39, 0xB4, 0x15, 0xDB, 0x10, 0x5C, 0x42, 0x83};
	const u8 expected[16] = {0x2B, 0xD3, 0x7B, 0x99, 0xC4, 0xBF, 0xCB, 0xDD, 0xB4, 0x90, 0xB4, 0xF6, 0xB5, 0x11, 0x56, 0xA5};
	u8 output[16] = {};
	LTEngine::Hash::md5(data, sizeof(data), output);

	TEST_CHECK(std::memcmp(output, expected, sizeof(output)) == 0);
	TEST_DUMP("Expected", expected, sizeof(expected));
	TEST_DUMP("Got", output, sizeof(output));
}


TEST_LIST = {{"test_crc32", test_crc32},
             {"test_md5", test_md5},

             {NULL, NULL}};
