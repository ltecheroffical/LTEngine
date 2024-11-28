#ifndef _LTENGINE_FSTREAM_FILE_HPP_
#define _LTENGINE_FSTREAM_FILE_HPP_

#include <fstream>

#include <LTEngine/os/file.hpp>


namespace LTEngine::OS {
	class FStreamFile : public File {
	public:
		FStreamFile() : File(0) {}
		FStreamFile(const char *path, u8 mode);
		~FStreamFile() override;

		void open(const char *path, u8 mode);

		void seekp(size_t offset, Seek origin) override;
		size_t tellp() override;
		void seekg(size_t offset, Seek origin) override;
		size_t tellg() override;
		size_t size() override;

		bool eof() const override;

		size_t read(void *buffer, size_t size) override;
		void write(const void *buffer, size_t size) override;

		void flush() override;

		std::fstream *getStream() { return &m_stream; }

	private:
		std::fstream m_stream;
	};
} // namespace LTEngine::OS

#endif
