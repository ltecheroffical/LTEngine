#include <LTEngine/os/mem_file.hpp>


using namespace LTEngine;
using namespace LTEngine::OS;


MemFile::MemFile(u8 mode) : File(mode) {}

MemFile::MemFile(const void *data, size_t size, u8 mode) : File(mode) {
	m_buffer.insert(m_buffer.end(), reinterpret_cast<const u8 *>(data), reinterpret_cast<const u8 *>(data) + size);
}


void MemFile::seekp(size_t offset, Seek origin) {
	switch (origin) {
		case Seek::Begin:
			m_offset = offset;
			break;
		case Seek::Current:
			m_offset += offset;
			break;
		case Seek::End:
			m_offset = m_buffer.size() - offset;
			break;
	}
	m_offset = std::min(m_offset, m_buffer.size());
}

size_t MemFile::tellp() {
	return m_offset;
}

void MemFile::seekg(size_t offset, Seek origin) {
	switch (origin) {
		case Seek::Begin:
			m_offset = offset;
			break;
		case Seek::Current:
			m_offset += offset;
			break;
		case Seek::End:
			m_offset = m_buffer.size() - offset;
			break;
	}
	m_offset = std::min(m_offset, m_buffer.size());
}

size_t MemFile::tellg() {
	return m_offset;
}

size_t MemFile::size() {
	return m_buffer.size();
}


bool MemFile::eof() const {
	return m_offset >= m_buffer.size();
}


size_t MemFile::read(void *buffer, size_t size) {
	if (size == 0) { return 0; }
	if (m_offset + size > m_buffer.size()) { size = m_buffer.size() - m_offset; }
	memcpy(buffer, m_buffer.data() + m_offset, size);
	m_offset += size;
	return size;
}

void MemFile::write(const void *buffer, size_t size) {
	if (getMode() & FLAG_FILE_APPEND) {
		m_buffer.insert(m_buffer.begin() + m_offset, reinterpret_cast<const u8 *>(buffer),
		                reinterpret_cast<const u8 *>(buffer) + size);
	} else if (getMode() & FLAG_FILE_WRITE) {
		// Ensure we have enough space
		if (m_offset + size > m_buffer.size()) { m_buffer.resize(m_buffer.size() + (size - (m_buffer.size() - m_offset))); }
		memcpy(m_buffer.data() + m_offset, buffer, size);
	}
	m_offset += size;
}


void MemFile::flush() {
	// No op
}
