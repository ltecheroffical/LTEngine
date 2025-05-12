#ifndef _LTCORE_EXC_NOT_IMPLMENTED_
#define _LTCORE_EXC_NOT_IMPLMENTED_

#include <stdexcept>


namespace LTCore {
	class NotImplementedException : public std::runtime_error {
	public:
		NotImplementedException(const std::string &message) : std::runtime_error(message) {
		}
		NotImplementedException(const NotImplementedException &other) : std::runtime_error(other) {
		}
		~NotImplementedException() throw() {
		}
	};
} // namespace LTCore

#endif
