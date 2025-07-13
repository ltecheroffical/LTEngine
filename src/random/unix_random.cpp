#include <limits>

#include <LTEngine/random/unix_random.hpp>


using namespace LTEngine;
using namespace LTEngine::Random;


UnixRandom::UnixRandom(size_t buffer_size) {
	_buffer_size = buffer_size;

	_urandom.open("/dev/urandom", std::ios::in | std::ios::binary);
	if (!_urandom.is_open()) { throw std::runtime_error("Failed to open /dev/urandom"); }

	_buffer.resize(_buffer_size);

	_urandom.read(reinterpret_cast<char *>(&_buffer[0]), _buffer_size);
}

UnixRandom::~UnixRandom() {
	_urandom.close();
}


u8 UnixRandom::next_u8() {
	if (_buffer.size() <= 0) {
		_buffer.resize(_buffer_size);
		_urandom.read(reinterpret_cast<char *>(&_buffer[0]), _buffer_size);
	}

	u8 value = _buffer.back();
	_buffer.pop_back();
	return value;
}

u16 UnixRandom::next_u16() {
	return next_u8() | (next_u8() << 8);
}

u32 UnixRandom::next_u32() {
	return next_u16() | (next_u16() << 16);
}

u64 UnixRandom::next_u64() {
	return next_u32() | ((u64)next_u16() << 32);
}


i8 UnixRandom::next_i8() {
	u8 value = next_u8();
	return *reinterpret_cast<i8 *>(&value);
}

i16 UnixRandom::next_i16() {
	u16 value = next_u16();
	return *reinterpret_cast<i16 *>(&value);
}

i32 UnixRandom::next_i32() {
	u32 value = next_u32();
	return *reinterpret_cast<i32 *>(&value);
}

i64 UnixRandom::next_i64() {
	u64 value = next_u64();
	return *reinterpret_cast<i64 *>(&value);
}


f32 UnixRandom::next_f32() {
	return (f32)next_u16() / std::numeric_limits<u16>::max();
}

f64 UnixRandom::next_f64() {
	return (f64)next_u32() / std::numeric_limits<u32>::max();
}


void UnixRandom::next_bytes(void *data, size_t size) {
	for (size_t i = 0; i < size; i++) { ((u8 *)data)[i] = next_u8(); }
}
