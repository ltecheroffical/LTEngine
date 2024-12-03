#ifndef _LTENGINE_MEM_FILE_HPP_
#define _LTENGINE_MEM_FILE_HPP_

#include <vector>

#include <LTEngine/os/file.hpp>

#include <LTEngine/common/compiler_utils.h>


namespace LTEngine::OS {
	class LTENGINE_API MemFile : public File {
	public:
		MemFile(u8 mode);
		MemFile(const void *buffer, size_t size, u8 mode);
		~MemFile() override = default;

		void seekp(size_t offset, Seek origin) override;
		size_t tellp() override;
		void seekg(size_t offset, Seek origin) override;
		size_t tellg() override;
		size_t size() override;

		bool eof() const override;

		size_t read(void *buffer, size_t size) override;
		void write(const void *buffer, size_t size) override;

		void flush() override;

		void getBuffer(void *buffer) { memcpy(buffer, m_buffer.data(), m_buffer.size()); }

	private:
		std::vector<u8> m_buffer;
		size_t m_offset = 0;
	};
} // namespace LTEngine::OS

#endif
