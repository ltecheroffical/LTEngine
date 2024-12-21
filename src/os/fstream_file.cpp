#include <LTEngine/os/fstream_file.hpp>


using namespace LTEngine;
using namespace LTEngine::OS;


FStreamFile::FStreamFile(const char *path, u8 mode) : File(mode) {
	open(path, mode);
}

FStreamFile::~FStreamFile() {
	m_stream.close();
}


void FStreamFile::open(const char *path, u8 mode) {
	std::ios::openmode openMode = std::ios::openmode{};
	bool create = (mode & FLAG_FILE_CREATE) != 0;

	if (mode & FLAG_FILE_READ) openMode |= std::ios::in;
	if (mode & FLAG_FILE_WRITE) openMode |= std::ios::out;
	if (mode & FLAG_FILE_APPEND) openMode |= std::ios::app;

	if (m_stream.is_open()) { m_stream.close(); }

	m_stream.open(path, openMode);
	if (!m_stream.is_open()) {
		if (create) {
			m_stream.open(path, std::ios::out);
			m_stream.close();
			m_stream.open(path, openMode);
			return;
		}
		throw std::runtime_error("Failed to open file: " + std::string(path));
	}

	setMode(mode);
}


void FStreamFile::seekp(size_t offset, Seek origin) {
	std::ios_base::seekdir dir;
	switch (origin) {
		case Seek::Begin:
			dir = std::ios_base::beg;
			break;
		case Seek::Current:
			dir = std::ios_base::cur;
			break;
		case Seek::End:
			dir = std::ios_base::end;
			break;
	}
	m_stream.seekp(offset, dir);
}

size_t FStreamFile::tellp() {
	return m_stream.tellp();
}

void FStreamFile::seekg(size_t offset, Seek origin) {
	std::ios_base::seekdir dir;
	switch (origin) {
		case Seek::Begin:
			dir = std::ios_base::beg;
			break;
		case Seek::Current:
			dir = std::ios_base::cur;
			break;
		case Seek::End:
			dir = std::ios_base::end;
			break;
	}
	m_stream.seekg(offset, dir);
}

size_t FStreamFile::tellg() {
	return m_stream.tellg();
}

size_t FStreamFile::size() {
	std::ios::pos_type pos = m_stream.tellp();

	m_stream.seekg(0, std::ios::end);
	size_t size = m_stream.tellg();
	m_stream.seekg(pos, std::ios::beg);
	return size;
}


bool FStreamFile::eof() const {
	return m_stream.eof();
}


size_t FStreamFile::read(void *buffer, size_t size) {
	return m_stream.read(reinterpret_cast<char *>(buffer), size).gcount();
}

void FStreamFile::write(const void *buffer, size_t size) {
	m_stream.write(reinterpret_cast<const char *>(buffer), size);
}


void FStreamFile::flush() {
	m_stream.flush();
}
