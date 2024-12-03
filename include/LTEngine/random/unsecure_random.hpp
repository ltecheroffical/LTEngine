#ifndef _LTENGINE_RANDOM_UNSECURE_RANDOM_HPP_
#define _LTENGINE_RANDOM_UNSECURE_RANDOM_HPP_

#include <LTEngine/random/random.hpp>


namespace LTEngine::Random {
	class RandomUnsecure : public Random {
	public:
		RandomUnsecure() = default;
		virtual ~RandomUnsecure() = default;

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

		void nextBytes(void *data, size_t size) override;

		void seed(u64 seed);

	private:
		u16 m_index = 0;
	};
} // namespace LTEngine::Random

#endif
