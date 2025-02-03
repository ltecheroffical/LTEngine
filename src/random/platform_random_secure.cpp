#include <LTEngine/random/platform_random_secure.hpp>


using namespace LTEngine;
using namespace LTEngine::Random;

#if defined(__linux__) || defined(__APPLE__)
PlatformRandomSecure::PlatformRandomSecure(RandomSettings settings) : m_random(settings.unixRandomBufferSize) {
}
#else
PlatformRandomSecure::PlatformRandomSecure(RandomSettings settings) : m_random() {
}
#endif


u8 PlatformRandomSecure::next_u8() {
	return m_random.next_u8();
}

u16 PlatformRandomSecure::next_u16() {
	return m_random.next_u16();
}

u32 PlatformRandomSecure::next_u32() {
	return m_random.next_u32();
}

u64 PlatformRandomSecure::next_u64() {
	return m_random.next_u64();
}


i8 PlatformRandomSecure::next_i8() {
	return m_random.next_i8();
}

i16 PlatformRandomSecure::next_i16() {
	return m_random.next_i16();
}

i32 PlatformRandomSecure::next_i32() {
	return m_random.next_i32();
}

i64 PlatformRandomSecure::next_i64() {
	return m_random.next_i64();
}


f32 PlatformRandomSecure::next_f32() {
	return m_random.next_f32();
}

f64 PlatformRandomSecure::next_f64() {
	return m_random.next_f64();
}


void PlatformRandomSecure::nextBytes(void *data, size_t size) {
	m_random.nextBytes(data, size);
}
