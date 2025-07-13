#ifndef _LTENGINE_RANDOM_MT19937_HPP_
#define _LTENGINE_RANDOM_MT19937_HPP_


#include <random>

#include <LTEngine/random/random.hpp>


namespace LTEngine::Random {
	class LTENGINE_API MT19937 : public Random {
	public:
		MT19937();
		~MT19937() override = default;

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

	private:
		std::mt19937 m_generator;
	};
} // namespace LTEngine::Random

#endif
