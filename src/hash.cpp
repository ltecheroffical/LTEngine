#include <vector>

#include <LTEngine/hash.hpp>


u32 LTEngine::Hash::crc32(const u8 *data, u32 size) {
	static u32 table[256];
	static bool initialized = false;

	if (!initialized) {
		for (u32 i = 0; i < 256; i++) {
			u32 crc = i;
			for (u32 j = 0; j < 8; j++) { crc = (crc >> 1) ^ (crc & 1 ? 0xedb88320 : 0); }
			table[i] = crc;
		}
		initialized = true;
	}

	u32 crc = 0xffffffff;
	for (u32 i = 0; i < size; i++) { crc = (crc >> 8) ^ table[(crc & 0xff) ^ data[i]]; }
	return crc ^ 0xffffffff;
}


void LTEngine::Hash::md5(const u8 *data, u32 size, u8 output[16]) {
	const u32 s[] = {7,  12, 17, 22, 7,  12, 17, 22, 7,  12, 17, 22, 7,  12, 17, 22, 5,  9,  14, 20, 5,  9,
	                 14, 20, 5,  9,  14, 20, 5,  9,  14, 20, 4,  11, 16, 23, 4,  11, 16, 23, 4,  11, 16, 23,
	                 4,  11, 16, 23, 6,  10, 15, 21, 6,  10, 15, 21, 6,  10, 15, 21, 6,  10, 15, 21};

	static u32 k[64];
	static bool initialized = false;

	if (!initialized) {
		for (u32 i = 0; i < 64; i++) { k[i] = floor(pow(2, 32) * abs(sin(i + 1))); }
		initialized = true;
	}

	const auto rotateLeft = [](u32 x, u32 n) {
		return (x << n) | (x >> (32 - n));
	};

	u32 a0 = 0x67452301;
	u32 b0 = 0xEFCDAB89;
	u32 c0 = 0x98BADCFE;
	u32 d0 = 0x10325476;

	std::vector<u8> processedData;
	processedData.insert(processedData.end(), data, data + size);

	// Pre-processing: Add a single bit
	processedData.push_back(0x80);

	// Pre-processing: Pad with zeros until length is 56 bytes
	u32 padding = (56 - (processedData.size() % 64)) % 64;
	for (u32 p = 0; p < padding; p++) { processedData.push_back(0x00); }


	// Pre-processing: Append length in bits
	u64 length = size * 8;
	for (u32 i = 0; i < 8; i++) { processedData.push_back((length >> (i * 8)) & 0xff); }

	for (u32 i = 0; i < processedData.size(); i += 64) {
		u32 M[16];
		for (u32 m = 0; m < 16; m++) {
			M[m] = (processedData[i + m * 4 + 0]) | (processedData[i + m * 4 + 1] << 8) | (processedData[i + m * 4 + 2] << 16) |
			       (processedData[i + m * 4 + 3] << 24);
		}

		u32 a = a0;
		u32 b = b0;
		u32 c = c0;
		u32 d = d0;

		for (u32 j = 0; j < 64; j++) {
			u32 f, g;
			if (j < 16) {
				f = (b & c) | ((~b) & d);
				g = j;
			} else if (j < 32) {
				f = (d & b) | ((~d) & c);
				g = (5 * j + 1) % 16;
			} else if (j < 48) {
				f = b ^ c ^ d;
				g = (3 * j + 5) % 16;
			} else {
				f = c ^ (b | (~d));
				g = (7 * j) % 16;
			}

			u32 temp = d;
			d = c;
			c = b;
			b = b + rotateLeft(a + f + k[j] + M[g], s[j]);
			a = temp;
		}

		a0 = a0 + a;
		b0 = b0 + b;
		c0 = c0 + c;
		d0 = d0 + d;
	}

	output[0] = (u8)(a0);
	output[1] = (u8)(a0 >> 8);
	output[2] = (u8)(a0 >> 16);
	output[3] = (u8)(a0 >> 24);
	output[4] = (u8)(b0);
	output[5] = (u8)(b0 >> 8);
	output[6] = (u8)(b0 >> 16);
	output[7] = (u8)(b0 >> 24);
	output[8] = (u8)(c0);
	output[9] = (u8)(c0 >> 8);
	output[10] = (u8)(c0 >> 16);
	output[11] = (u8)(c0 >> 24);
	output[12] = (u8)(d0);
	output[13] = (u8)(d0 >> 8);
	output[14] = (u8)(d0 >> 16);
	output[15] = (u8)(d0 >> 24);
}
