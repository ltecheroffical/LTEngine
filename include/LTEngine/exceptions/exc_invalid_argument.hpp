#ifndef _LTENGINE_EXC_INVALID_ARGUMENT_
#define _LTENGINE_EXC_INVALID_ARGUMENT_

#include <LTEngine/exceptions/exc_invalid_data.hpp>

namespace LTEngine {
	class InvalidArgumentException : public InvalidDataException {
	public:
		InvalidArgumentException(std::string message) throw() : InvalidDataException(message) {
		}
		InvalidArgumentException(const InvalidArgumentException &other) throw() : InvalidDataException(other) {
		}
		~InvalidArgumentException() throw() {
		}
	};
} // namespace LTEngine

#endif
