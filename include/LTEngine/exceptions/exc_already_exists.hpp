#ifndef _LTENGINE_EXC_ALREADY_EXISTS_
#define _LTENGINE_EXC_ALREADY_EXISTS_

#include <LTEngine/exceptions/exc_conflict.hpp>


namespace LTEngine {
	class AlreadyExistsException : public ConflictException {
	public:
		AlreadyExistsException(std::string message) : ConflictException(message) {
		}
		AlreadyExistsException(const AlreadyExistsException &other) : ConflictException(other) {
		}
		~AlreadyExistsException() throw() {
		}
	};
} // namespace LTEngine

#endif
