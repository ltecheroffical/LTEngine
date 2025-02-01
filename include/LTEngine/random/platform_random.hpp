#include <LTEngine/random/random.hpp>


namespace LTEngine::Random {
	// This class has the purpose of choosing the best for platform randomness
	class LTENGINE_API PlatformRandom : public Random {
	public:
		struct RandomSettings {
			size_t unixRandomBufferSize = 512;
		};

		PlatformRandom(RandomSettings settings);
		~PlatformRandom() override = default;

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
		std::unique_ptr<Random> m_random;
	};
} // namespace LTEngine::Random
