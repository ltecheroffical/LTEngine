#include <LTEngine/os/mem_file.hpp>


using namespace LTEngine;
using namespace LTEngine::OS;

MemFile::MemFile(u8 mode)
    : File(mode) {
}

MemFile::MemFile(const void *data, size_t size, u8 mode)
    : File(mode) {
	_buffer.insert(_buffer.end(), reinterpret_cast<const u8 *>(data), reinterpret_cast<const u8 *>(data) + size);
}

void MemFile::clear() {
	_buffer.clear();
}

void MemFile::seekp(size_t offset, Seek origin) {
	switch (origin) {
		case Seek::BEGIN:
			_offset = offset;
			break;
		case Seek::CURRENT:
			_offset += offset;
			break;
		case Seek::END:
			_offset = _buffer.size() - offset;
			break;
	}
	_offset = std::min(_offset, _buffer.size());
}

size_t MemFile::tellp() {
	return _offset;
}

void MemFile::seekg(size_t offset, Seek origin) {
	switch (origin) {
		case Seek::BEGIN:
			_offset = offset;
			break;
		case Seek::CURRENT:
			_offset += offset;
			break;
		case Seek::END:
			_offset = _buffer.size() - offset;
			break;
	}
	_offset = std::min(_offset, _buffer.size());
}

size_t MemFile::tellg() {
	return _offset;
}

size_t MemFile::size() {
	return _buffer.size();
}

bool MemFile::eof() const {
	return _offset >= _buffer.size();
}

size_t MemFile::read(void *buffer, size_t size) {
	if (size == 0) {
		return 0;
	}
	if (_offset + size > _buffer.size()) {
		size = _buffer.size() - _offset;
	}
	memcpy(buffer, _buffer.data() + _offset, size);
	_offset += size;
	return size;
}

void MemFile::write(const void *buffer, size_t size) {
	if (get_mode() & FLAG_FILE_APPEND) {
		_buffer.insert(_buffer.begin() + _offset, reinterpret_cast<const u8 *>(buffer),
		                reinterpret_cast<const u8 *>(buffer) + size);
	} else if (get_mode() & FLAG_FILE_WRITE) {
		// Ensure we have enough space
		if (_offset + size > _buffer.size()) {
			_buffer.resize(_buffer.size() + (size - (_buffer.size() - _offset)));
		}
		memcpy(_buffer.data() + _offset, buffer, size);
	}
	_offset += size;
}

void MemFile::flush() {
	// No op
}
