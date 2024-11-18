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


void md5(const u8 *data, u32 size, u8 output[16]) {
	auto F = [](u32 x, u32 y, u32 z) {
		return (x & y) | (~x & z);
	};
	auto G = [](u32 x, u32 y, u32 z) {
		return (x & z) | (y & ~z);
	};
	auto H = [](u32 x, u32 y, u32 z) {
		return x ^ y ^ z;
	};
	auto I = [](u32 x, u32 y, u32 z) {
		return y ^ (x | ~z);
	};

	auto rotateLeft = [](u32 x, u32 n) {
		return (x << n) | (x >> (32 - n));
	};

	u32 a = 0x10325476;
	u32 b = 0x98badcfe;
	u32 c = 0xefcdab89;
	u32 d = 0x67452301;


	std::vector<u8> processedData(size);
	processedData.insert(processedData.end(), data, data + size);

	// Step 1: Append the bit '1' to the end
	processedData.push_back(0x80);

	// Step 2: Append 0's
	while ((processedData.size() % 64) != (64 - 8)) { processedData.push_back(0); }

	// Step 3: Append the length
	u64 bits = size * 8;
	for (u32 i = 0; i < 8; i++) { processedData.push_back((bits >> (i * 8)) & 0xff); }

	// define k and s (Clang format cleans it up to a nice format)
	u32 k[64] = {
	    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af,
	    0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	};

	u32 s[64] = {7,  12, 17, 22, 7,  12, 17, 22, 7,  12, 17, 22, 7,  12, 17, 22, 5,  9,  14, 20, 5,  9,
	             14, 20, 5,  9,  14, 20, 5,  9,  14, 20, 4,  11, 16, 23, 4,  11, 16, 23, 4,  11, 16, 23,
	             4,  11, 16, 23, 6,  10, 15, 21, 6,  10, 15, 21, 6,  10, 15, 21, 6,  10, 15, 21};


	for (u32 i = 0; i < processedData.size(); i += 64) {
		u32 block[16];
		for (u32 j = 0; j < 16; j++) {
			block[j] = (processedData[i + j * 4] << 24) | (processedData[i + j * 4 + 1] << 16) |
			           (processedData[i + j * 4 + 2] << 8) | processedData[i + j * 4 + 3];
		}

		u32 aa = a;
		u32 bb = b;
		u32 cc = c;
		u32 dd = d;

		for (u32 j = 0; j < 64; j++) {
			u32 f;
			u32 g;
			if (j < 16) {
				f = F(bb, cc, dd);
				g = j;
			} else if (j < 32) {
				f = G(bb, cc, dd);
				g = (5 * j + 1) % 16;
			} else if (j < 48) {
				f = H(bb, cc, dd);
				g = (3 * j + 5) % 16;
			} else {
				f = I(bb, cc, dd);
				g = (7 * j) % 16;
			}

			u32 temp = dd;
			dd = cc;
			cc = bb;
			bb = bb + rotateLeft(a + f + block[g] + k[j], s[j]);
			a = temp;
		}

		a += aa;
		b += bb;
		c += cc;
		d += dd;
	}

	for (u32 i = 0; i < 4; i++) {
		output[i] = (a >> (i * 8)) & 0xff;
		output[i + 4] = (b >> (i * 8)) & 0xff;
		output[i + 8] = (c >> (i * 8)) & 0xff;
		output[i + 12] = (d >> (i * 8)) & 0xff;
	}
}
