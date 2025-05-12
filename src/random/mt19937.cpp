#include <LTCore/random/mt19937.hpp>


using namespace LTCore;
using namespace LTCore::Random;


MT19937::MT19937() {
	m_generator.seed(std::random_device{}());
}


u8 MT19937::next_u8() {
	std::uniform_int_distribution<u8> distribution;
	return distribution(m_generator);
}

u16 MT19937::next_u16() {
	std::uniform_int_distribution<u16> distribution;
	return distribution(m_generator);
}

u32 MT19937::next_u32() {
	std::uniform_int_distribution<u32> distribution;
	return distribution(m_generator);
}

u64 MT19937::next_u64() {
	std::uniform_int_distribution<u64> distribution;
	return distribution(m_generator);
}


i8 MT19937::next_i8() {
	u8 value = next_u8();
	return *reinterpret_cast<i8 *>(&value);
}

i16 MT19937::next_i16() {
	u16 value = next_u16();
	return *reinterpret_cast<i16 *>(&value);
}

i32 MT19937::next_i32() {
	u32 value = next_u32();
	return *reinterpret_cast<i32 *>(&value);
}

i64 MT19937::next_i64() {
	u64 value = next_u64();
	return *reinterpret_cast<i64 *>(&value);
}


f32 MT19937::next_f32() {
	return (f32)next_u16() / std::numeric_limits<u16>::max();
}

f64 MT19937::next_f64() {
	return (f64)next_u32() / std::numeric_limits<u32>::max();
}


void MT19937::nextBytes(void *data, size_t size) {
	std::uniform_int_distribution<u8> distribution;
	for (size_t i = 0; i < size; i++) {
		*reinterpret_cast<u8 *>(&((u8 *)data)[i]) = distribution(m_generator);
	}
}
