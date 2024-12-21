#ifndef _LTENGINE_FILE_HPP_
#define _LTENGINE_FILE_HPP_

#include <cstddef>

#include <LTEngine/common/types/inttypes.h>

#include <LTEngine/common/compiler_utils.h>


namespace LTEngine::OS {
	class File {
	public:
		static const u8 FLAG_FILE_READ;
		static const u8 FLAG_FILE_WRITE;
		static const u8 FLAG_FILE_APPEND;
		static const u8 FLAG_FILE_CREATE;

		enum class Seek { Begin, Current, End };

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

	inline const u8 File::FLAG_FILE_READ = (u8)(1 << 0);
	inline const u8 File::FLAG_FILE_WRITE = (u8)(1 << 1);
	inline const u8 File::FLAG_FILE_APPEND = (u8)(1 << 2);
	inline const u8 File::FLAG_FILE_CREATE = (u8)(1 << 7);
} // namespace LTEngine::OS

#endif
