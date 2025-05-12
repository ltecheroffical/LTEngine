#ifndef _LTCORE_RANDOM_UNIX_RANDOM_SECURE_HPP_
#define _LTCORE_RANDOM_UNIX_RANDOM_SECURE_HPP_

#include <fstream>
#include <vector>

#include <LTCore/random/random.hpp>


namespace LTCore::Random {
	class LTCORE_API UnixRandomSecure : public Random {
	public:
		UnixRandomSecure(size_t bufferSize = 512);
		~UnixRandomSecure() override;

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
		u32 m_bufferSize;
		std::vector<u8> m_buffer;

		std::ifstream m_random;
	};
} // namespace LTCore::Random

#endif
