#ifndef _LTENGINE_RANDOM_UNIX_RANDOM_SECURE_HPP_
#define _LTENGINE_RANDOM_UNIX_RANDOM_SECURE_HPP_

#include <fstream>
#include <vector>

#include <LTEngine/random/random.hpp>


namespace LTEngine::Random {
	class LTENGINE_API UnixRandomSecure : public Random {
	public:
		UnixRandomSecure(size_t buffer_size = 512);
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

		void next_bytes(void *data, size_t size) ;

	private:
		u32 _buffer_size;
		std::vector<u8> _buffer;

		std::ifstream _random;
	};
} // namespace LTEngine::Random

#endif
