#ifndef _LTENGINE_RANDOM_HPP_
#define _LTENGINE_RANDOM_HPP_

#include <LTEngine/common/compiler_utils.h>


namespace LTEngine::Random {
	class Random {
	public:
		virtual ~Random() = default;

		virtual u8 next_u8() = 0;
		virtual u16 next_u16() = 0;
		virtual u32 next_u32() = 0;
		virtual u64 next_u64() = 0;

		virtual i8 next_i8() = 0;
		virtual i16 next_i16() = 0;
		virtual i32 next_i32() = 0;
		virtual i64 next_i64() = 0;

		virtual f32 next_f32() = 0;
		virtual f64 next_f64() = 0;

		virtual void nextBytes(void *data, size_t size) = 0;
	};
} // namespace LTEngine::Random

#endif
