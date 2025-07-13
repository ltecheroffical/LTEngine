#ifndef _LTENGINE_MEM_FILE_HPP_
#define _LTENGINE_MEM_FILE_HPP_

#include <vector>

#include <LTEngine/os/file.hpp>

namespace LTEngine::OS {
class LTENGINE_API MemFile : public File {
  public:
	MemFile(u8 mode);
	MemFile(const void *buffer, size_t size, u8 mode);
	~MemFile() override = default;

	void clear() override;

	void seekp(size_t offset, Seek origin) override;
	size_t tellp() override;
	void seekg(size_t offset, Seek origin) override;
	size_t tellg() override;
	size_t size() override;

	bool eof() const override;

	size_t read(void *buffer, size_t size) override;
	void write(const void *buffer, size_t size) override;

	void flush() override;

	void get_buffer(void *buffer) {
		memcpy(buffer, _buffer.data(), _buffer.size());
	}

  private:
	std::vector<u8> _buffer;
	size_t _offset = 0;
};
} // namespace LTEngine::OS

#endif
