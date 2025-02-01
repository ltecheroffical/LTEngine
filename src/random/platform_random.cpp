#include <LTEngine/random/platform_random.hpp>

#include <LTEngine/random/mt19937.hpp>
#include <LTEngine/random/unix_random.hpp>


using namespace LTEngine;
using namespace LTEngine::Random;


PlatformRandom::PlatformRandom(RandomSettings settings) {
#if defined(__linux__) || defined(__APPLE__)
	m_random = std::make_unique<UnixRandom>(settings.unixRandomBufferSize);
#else
	m_random = std::make_unique<MT19937>();
#endif
}


u8 PlatformRandom::next_u8() {
	return m_random->next_u8();
}

u16 PlatformRandom::next_u16() {
	return m_random->next_u16();
}

u32 PlatformRandom::next_u32() {
	return m_random->next_u32();
}

u64 PlatformRandom::next_u64() {
	return m_random->next_u64();
}


i8 PlatformRandom::next_i8() {
	return m_random->next_i8();
}

i16 PlatformRandom::next_i16() {
	return m_random->next_i16();
}

i32 PlatformRandom::next_i32() {
	return m_random->next_i32();
}

i64 PlatformRandom::next_i64() {
	return m_random->next_i64();
}


f32 PlatformRandom::next_f32() {
	return m_random->next_f32();
}

f64 PlatformRandom::next_f64() {
	return m_random->next_f64();
}
