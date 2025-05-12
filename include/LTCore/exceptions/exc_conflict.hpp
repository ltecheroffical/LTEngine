#ifndef _LTCORE_EXC_CONFLICT_
#define _LTCORE_EXC_CONFLICT_

#include <stdexcept>


namespace LTCore {
	class ConflictException : public std::runtime_error {
	public:
		ConflictException(std::string message) : std::runtime_error(message) {
		}
		ConflictException(const ConflictException &other) : std::runtime_error(other) {
		}
		~ConflictException() throw() {
		}
	};
} // namespace LTCore

#endif
