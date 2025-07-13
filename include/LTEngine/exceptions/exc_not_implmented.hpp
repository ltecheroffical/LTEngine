#ifndef _LTENGINE_EXC_NOT_IMPLMENTED_
#define _LTENGINE_EXC_NOT_IMPLMENTED_

#include <stdexcept>


namespace LTEngine {
	class NotImplementedException : public std::runtime_error {
	public:
		NotImplementedException(const std::string &message) : std::runtime_error(message) {
		}
		NotImplementedException(const NotImplementedException &other) : std::runtime_error(other) {
		}
		~NotImplementedException() throw() {
		}
	};
} // namespace LTEngine

#endif
