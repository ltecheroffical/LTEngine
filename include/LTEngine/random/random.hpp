#ifndef _LTENGINE_RANDOM_HPP_
#define _LTENGINE_RANDOM_HPP_

#include <LTEngine/common/types/floattypes.h>
#include <LTEngine/common/types/inttypes.h>


namespace LTEngine::Random {
	class Random {
	public:
		virtual ~Random() = 0;

		virtual u8 next_u8();
		virtual u16 next_u16();
		virtual u32 next_u32();
		virtual u64 next_u64();

		virtual i8 next_i8();
		virtual i16 next_i16();
		virtual i32 next_i32();
		virtual i64 next_i64();

		virtual f32 next_f32();
		virtual f64 next_f64();

		virtual void nextBytes(u8 *data, size_t length);
	};
} // namespace LTEngine::Random

#endif
