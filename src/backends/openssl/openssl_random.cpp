#include <limits>

#include <LTEngine/backends/openssl/openssl_random.hpp>


using namespace LTEngine;
using namespace LTEngine::Random;


u8 OpenSSLRandom::next_u8() {
	u8 value;
	if (RAND_bytes((unsigned char *)&value, sizeof(u8)) != 1) {
		throw std::runtime_error("Failed to generate random number");
	}
	return value;
}

u16 OpenSSLRandom::next_u16() {
	u16 value;
	if (RAND_bytes((unsigned char *)&value, sizeof(u16)) != 1) {
		throw std::runtime_error("Failed to generate random number");
	}
	return value;
}

u32 OpenSSLRandom::next_u32() {
	u32 value;
	if (RAND_bytes((unsigned char *)&value, sizeof(u32)) != 1) {
		throw std::runtime_error("Failed to generate random number");
	}
	return value;
}

u64 OpenSSLRandom::next_u64() {
	u64 value;
	if (RAND_bytes((unsigned char *)&value, sizeof(u64)) != 1) {
		throw std::runtime_error("Failed to generate random number");
	}
	return value;
}


i8 OpenSSLRandom::next_i8() {
	u8 value;
	if (RAND_bytes((unsigned char *)&value, sizeof(i8)) != 1) {
		throw std::runtime_error("Failed to generate random number");
	}
	return *reinterpret_cast<i8 *>(&value);
}

i16 OpenSSLRandom::next_i16() {
	u16 value;
	if (RAND_bytes((unsigned char *)&value, sizeof(i16)) != 1) {
		throw std::runtime_error("Failed to generate random number");
	}
	return *reinterpret_cast<i16 *>(&value);
}

i32 OpenSSLRandom::next_i32() {
	u32 value;
	if (RAND_bytes((unsigned char *)&value, sizeof(i32)) != 1) {
		throw std::runtime_error("Failed to generate random number");
	}
	return *reinterpret_cast<i32 *>(&value);
}

i64 OpenSSLRandom::next_i64() {
	u64 value;
	if (RAND_bytes((unsigned char *)&value, sizeof(i64)) != 1) {
		throw std::runtime_error("Failed to generate random number");
	}
	return *reinterpret_cast<i64 *>(&value);
}


f32 OpenSSLRandom::next_f32() {
	return (f32)next_u16() / std::numeric_limits<u16>::max();
}

f64 OpenSSLRandom::next_f64() {
	return (f64)next_u32() / std::numeric_limits<u32>::max();
}


void OpenSSLRandom::nextBytes(void *data, size_t size) {
	RAND_bytes((unsigned char *)data, size);
}
