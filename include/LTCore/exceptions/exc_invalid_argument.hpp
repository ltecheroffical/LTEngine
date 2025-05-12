#ifndef _LTCORE_EXC_INVALID_ARGUMENT_
#define _LTCORE_EXC_INVALID_ARGUMENT_

#include <LTCore/exceptions/exc_invalid_data.hpp>

namespace LTCore {
	class InvalidArgumentException : public InvalidDataException {
	public:
		InvalidArgumentException(std::string message) throw() : InvalidDataException(message) {
		}
		InvalidArgumentException(const InvalidArgumentException &other) throw() : InvalidDataException(other) {
		}
		~InvalidArgumentException() throw() {
		}
	};
} // namespace LTCore

#endif
