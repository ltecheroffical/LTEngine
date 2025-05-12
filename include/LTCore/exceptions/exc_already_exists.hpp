#ifndef _LTCORE_EXC_ALREADY_EXISTS_
#define _LTCORE_EXC_ALREADY_EXISTS_

#include <LTCore/exceptions/exc_conflict.hpp>


namespace LTCore {
	class AlreadyExistsException : public ConflictException {
	public:
		AlreadyExistsException(std::string message) : ConflictException(message) {
		}
		AlreadyExistsException(const AlreadyExistsException &other) : ConflictException(other) {
		}
		~AlreadyExistsException() throw() {
		}
	};
} // namespace LTCore

#endif
