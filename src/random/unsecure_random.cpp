#include <limits>

#include <LTEngine/random/unsecure_random.hpp>


using namespace LTEngine;
using namespace LTEngine::Random;


u8 RandomUnsecure::next_u8() {
	m_seed = m_seed * 1103515245 + 12345 / 2 - 124783; // Random function
	return ((u8)(m_seed)) ^ ((u8)(m_seed >> 8)) ^ ((u8)(m_seed >> 16)) ^ ((u8)(m_seed >> 24));
}

u16 RandomUnsecure::next_u16() {
	return (next_u8() << 8) | next_u8();
}

u32 RandomUnsecure::next_u32() {
	return (next_u16() << 16) | next_u16();
}

u64 RandomUnsecure::next_u64() {
	return ((u64)next_u32() << 32) | (u64)next_u32();
}


i8 RandomUnsecure::next_i8() {
	return (i8)next_u8();
}

i16 RandomUnsecure::next_i16() {
	return (i16)next_u16();
}

i32 RandomUnsecure::next_i32() {
	return (i32)next_u32();
}

i64 RandomUnsecure::next_i64() {
	return (i64)next_u64();
}


f32 RandomUnsecure::next_f32() {
	return (f32)next_u16() / std::numeric_limits<u16>::max();
}

f64 RandomUnsecure::next_f64() {
	return (f64)next_u32() / std::numeric_limits<u32>::max();
}


void RandomUnsecure::nextBytes(void *buffer, size_t size) {
	for (u32 i = 0; i < size; i++) {
		((u8 *)buffer)[i] = next_u8();
	}
}


void RandomUnsecure::seed(u64 seed) {
	m_seed = seed;
}
