#ifndef _LTENGINE_FILE_HPP_
#define _LTENGINE_FILE_HPP_

#include <cstddef>

#include <LTEngine/common/types/inttypes.h>


namespace LTEngine::OS {
	class File {
	public:
		enum class Seek { Begin, Current, End };

		static const u8 FILE_READ = (u8)(1 << 0);
		static const u8 FILE_WRITE = (u8)(1 << 1);
		static const u8 FILE_APPEND = (u8)(1 << 2);
		static const u8 FILE_CREATE = (u8)(1 << 7);

		File(u8 mode) : m_mode(mode) {}
		virtual ~File() = default;

		u8 getMode() const { return m_mode; }

		virtual void seekp(size_t offset, Seek origin) = 0;
		virtual size_t tellp() = 0;
		virtual void seekg(size_t offset, Seek origin) = 0;
		virtual size_t tellg() = 0;
		virtual size_t size() = 0;

		virtual bool eof() const = 0;

		virtual size_t read(void *buffer, size_t size) = 0;
		virtual void write(const void *buffer, size_t size) = 0;

		virtual void flush() = 0;

	protected:
		void setMode(u8 mode) { m_mode = mode; }

	private:
		u8 m_mode;
	};
} // namespace LTEngine::OS

#endif
