#ifndef _LTENGINE_OPENSSL_RANDOM_HPP_
#define _LTENGINE_OPENSSL_RANDOM_HPP_

#include <openssl/rand.h>

#include <LTEngine/common/compiler_utils.h>

#include <LTEngine/random/random.hpp>


namespace LTEngine::Random {
	// All functions may throw std::runtime_error
	class LTENGINE_API OpenSSLRandom : public Random {
	public:
		OpenSSLRandom() = default;
		~OpenSSLRandom() override = default;

		u8 next_u8() override;
		u16 next_u16() override;
		u32 next_u32() override;
		u64 next_u64() override;

		i8 next_i8() override;
		i16 next_i16() override;
		i32 next_i32() override;
		i64 next_i64() override;

		f32 next_f32() override;
		f64 next_f64() override;

		void next_bytes(void *data, size_t size) override;
	};
} // namespace LTEngine::Random

#endif
