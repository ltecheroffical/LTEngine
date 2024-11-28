#include <limits>

#include <LTEngine/random/unix_random.hpp>


using namespace LTEngine;
using namespace LTEngine::Random;


UnixRandom::UnixRandom(size_t bufferSize) {
	m_bufferSize = bufferSize;

	m_urandom.open("/dev/urandom", std::ios::in | std::ios::binary);
	if (!m_urandom.is_open()) { throw std::runtime_error("Failed to open /dev/urandom"); }

	m_buffer.resize(m_bufferSize);

	m_urandom.read(reinterpret_cast<char *>(&m_buffer[0]), m_bufferSize);
}

UnixRandom::~UnixRandom() {
	m_urandom.close();
}


u8 UnixRandom::next_u8() {
	if (m_buffer.size() <= 0) {
		m_buffer.resize(m_bufferSize);
		m_urandom.read(reinterpret_cast<char *>(&m_buffer[0]), m_bufferSize);
	}

	u8 value = m_buffer.back();
	m_buffer.pop_back();
	return value;
}

u16 UnixRandom::next_u16() {
	if (m_buffer.size() <= 0) {
		m_buffer.resize(m_bufferSize);
		m_urandom.read(reinterpret_cast<char *>(&m_buffer[0]), m_bufferSize);
	}

	u16 value = m_buffer.back() | m_buffer.back();
	m_buffer.pop_back();
	m_buffer.pop_back();
	return value;
}

u32 UnixRandom::next_u32() {
	if (m_buffer.size() <= 0) {
		m_buffer.resize(m_bufferSize);
		m_urandom.read(reinterpret_cast<char *>(&m_buffer[0]), m_bufferSize);
	}

	u32 value = m_buffer.back() | m_buffer.back() | m_buffer.back() | m_buffer.back();
	for (int i = 0; i < sizeof(u32); i++) { m_buffer.pop_back(); }
	return value;
}

u64 UnixRandom::next_u64() {
	if (m_buffer.size() <= 0) {
		m_buffer.resize(m_bufferSize);
		m_urandom.read(reinterpret_cast<char *>(&m_buffer[0]), m_bufferSize);
	}

	u64 value = m_buffer.back() | m_buffer.back() | m_buffer.back() | m_buffer.back() | m_buffer.back() | m_buffer.back() |
	            m_buffer.back() | m_buffer.back();
	for (int i = 0; i < sizeof(u64); i++) { m_buffer.pop_back(); }
	return value;
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
	return static_cast<f32>(next_u16()) / static_cast<f32>(std::numeric_limits<u16>::max());
}

f64 UnixRandom::next_f64() {
	return static_cast<f64>(next_u32()) / static_cast<f64>(std::numeric_limits<u32>::max());
}


void UnixRandom::nextBytes(u8 *data, size_t length) {
	for (size_t i = 0; i < length; i++) { data[i] = next_u8(); }
}
