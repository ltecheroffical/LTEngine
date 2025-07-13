#include <LTEngine/os/fstream_file.hpp>


using namespace LTEngine;
using namespace LTEngine::OS;

FStreamFile::FStreamFile(const char *path, u8 mode)
    : File(mode) {
	open(path, mode);
}

FStreamFile::~FStreamFile() {
	_stream.close();
}

void FStreamFile::open(const char *path, u8 mode) {
	std::ios::openmode open_mode = std::ios::openmode{};
	bool create = (mode & FLAG_FILE_CREATE) != 0;

	if (mode & FLAG_FILE_READ)
		open_mode |= std::ios::in;
	if (mode & FLAG_FILE_WRITE)
		open_mode |= std::ios::out;
	if (mode & FLAG_FILE_APPEND)
		open_mode |= std::ios::app;

	if (_stream.is_open()) {
		_stream.close();
	}

	_stream.open(path, open_mode);
	if (!_stream.is_open()) {
		if (create) {
			_stream.open(path, std::ios::out);
			_stream.close();
			_stream.open(path, open_mode);
		} else {
			throw std::runtime_error("Failed to open file: " + std::string(path));
		}
	}

	set_mode(mode);
	_path = path;
}

void FStreamFile::clear() {
	_stream.open(_path, std::ios::trunc);
	if (!_stream.is_open()) {
		throw std::runtime_error("Failed to clear file: " + std::string(_path));
	}
	_stream.close();

	std::ios::openmode open_mode = std::ios::openmode{};
	bool create = (get_mode() & FLAG_FILE_CREATE) != 0;

	if (get_mode() & FLAG_FILE_READ)
		open_mode |= std::ios::in;
	if (get_mode() & FLAG_FILE_WRITE)
		open_mode |= std::ios::out;
	if (get_mode() & FLAG_FILE_APPEND)
		open_mode |= std::ios::app;

	_stream.open(_path, open_mode);
	if (!_stream.is_open()) {
		throw std::runtime_error("Failed to open file: " + std::string(_path));
	}
}

void FStreamFile::seekp(size_t offset, Seek origin) {
	std::ios_base::seekdir dir;
	switch (origin) {
		case Seek::BEGIN:
			dir = std::ios_base::beg;
			break;
		case Seek::CURRENT:
			dir = std::ios_base::cur;
			break;
		case Seek::END:
			dir = std::ios_base::end;
			break;
	}
	_stream.seekp(offset, dir);
}

size_t FStreamFile::tellp() {
	return _stream.tellp();
}

void FStreamFile::seekg(size_t offset, Seek origin) {
	std::ios_base::seekdir dir;
	switch (origin) {
		case Seek::BEGIN:
			dir = std::ios_base::beg;
			break;
		case Seek::CURRENT:
			dir = std::ios_base::cur;
			break;
		case Seek::END:
			dir = std::ios_base::end;
			break;
	}
	_stream.seekg(offset, dir);
}

size_t FStreamFile::tellg() {
	return _stream.tellg();
}

size_t FStreamFile::size() {
	std::ios::pos_type pos = _stream.tellp();

	_stream.seekg(0, std::ios::end);
	size_t size = _stream.tellg();
	_stream.seekg(pos, std::ios::beg);
	return size;
}

bool FStreamFile::eof() const {
	return _stream.eof();
}

size_t FStreamFile::read(void *buffer, size_t size) {
	return _stream.read(reinterpret_cast<char *>(buffer), size).gcount();
}

void FStreamFile::write(const void *buffer, size_t size) {
	_stream.write(reinterpret_cast<const char *>(buffer), size);
}

void FStreamFile::flush() {
	_stream.flush();
}
