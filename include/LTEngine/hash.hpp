#ifndef _LTENGINE_HASH_HPP_
#define _LTENGINE_HASH_HPP_

#include <LTEngine/common/compiler_utils.h>


namespace LTEngine::Hash {
	u32 LTENGINE_API crc32(const u8 *data, u32 size);

	void LTENGINE_API md5(const u8 *data, u32 size, u8 output[16]);

	/* To be added in a future version, maybe v1.2.0?
	void sha1(const u8 *data, u32 size, u8 output[20]);
	void sha256(const u8 *data, u32 size, u8 output[32]);
	void sha512(const u8 *data, u32 size, u8 output[64]);
	*/
} // namespace LTEngine::Hash

#endif
