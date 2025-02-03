#include <limits>

#include <LTEngine/random/unix_random_secure.hpp>


using namespace LTEngine;
using namespace LTEngine::Random;


UnixRandomSecure::UnixRandomSecure(size_t bufferSize) {
	m_bufferSize = bufferSize;

	m_random.open("/dev/random", std::ios::in | std::ios::binary);
	if (!m_random.is_open()) {
		throw std::runtime_error("Failed to open /dev/random");
	}

	m_buffer.resize(m_bufferSize);

	m_random.read(reinterpret_cast<char *>(&m_buffer[0]), m_bufferSize);
}

UnixRandomSecure::~UnixRandomSecure() {
	m_random.close();
}


u8 UnixRandomSecure::next_u8() {
	if (m_buffer.size() <= 0) {
		m_buffer.resize(m_bufferSize);
		m_random.read(reinterpret_cast<char *>(&m_buffer[0]), m_bufferSize);
	}

	u8 value = m_buffer.back();
	m_buffer.pop_back();
	return value;
}

u16 UnixRandomSecure::next_u16() {
	if (m_buffer.size() <= 0) {
		m_buffer.resize(m_bufferSize);
		m_random.read(reinterpret_cast<char *>(&m_buffer[0]), m_bufferSize);
	}

	u16 value = m_buffer.back() | m_buffer.back();
	m_buffer.pop_back();
	m_buffer.pop_back();
	return value;
}

u32 UnixRandomSecure::next_u32() {
	if (m_buffer.size() <= 0) {
		m_buffer.resize(m_bufferSize);
		m_random.read(reinterpret_cast<char *>(&m_buffer[0]), m_bufferSize);
	}

	u32 value = m_buffer.back() | m_buffer.back() | m_buffer.back() | m_buffer.back();
	for (int i = 0; i < sizeof(u32); i++) {
		m_buffer.pop_back();
	}
	return value;
}

u64 UnixRandomSecure::next_u64() {
	if (m_buffer.size() <= 0) {
		m_buffer.resize(m_bufferSize);
		m_random.read(reinterpret_cast<char *>(&m_buffer[0]), m_bufferSize);
	}

	u64 value = m_buffer.back() | m_buffer.back() | m_buffer.back() | m_buffer.back() | m_buffer.back() | m_buffer.back() |
	            m_buffer.back() | m_buffer.back();
	for (int i = 0; i < sizeof(u64); i++) {
		m_buffer.pop_back();
	}
	return value;
}


i8 UnixRandomSecure::next_i8() {
	u8 value = next_u8();
	return *reinterpret_cast<i8 *>(&value);
}

i16 UnixRandomSecure::next_i16() {
	u16 value = next_u16();
	return *reinterpret_cast<i16 *>(&value);
}

i32 UnixRandomSecure::next_i32() {
	u32 value = next_u32();
	return *reinterpret_cast<i32 *>(&value);
}

i64 UnixRandomSecure::next_i64() {
	u64 value = next_u64();
	return *reinterpret_cast<i64 *>(&value);
}


f32 UnixRandomSecure::next_f32() {
	return (f32)next_u16() / std::numeric_limits<u16>::max();
}

f64 UnixRandomSecure::next_f64() {
	return (f64)next_u32() / std::numeric_limits<u32>::max();
}


void UnixRandomSecure::nextBytes(void *data, size_t size) {
	for (size_t i = 0; i < size; i++) {
		((u8 *)data)[i] = next_u8();
	}
}
