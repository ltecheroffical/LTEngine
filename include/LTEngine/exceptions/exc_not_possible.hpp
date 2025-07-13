#ifndef _LTENGINE_EXC_NOT_POSSIBLE_
#define _LTENGINE_EXC_NOT_POSSIBLE_

#include <stdexcept>

namespace LTEngine {
	class NotPossibleException : std::runtime_error {
	public:
		NotPossibleException(std::string message) throw() : std::runtime_error(message) {
		}
		NotPossibleException(const NotPossibleException &other) throw() : std::runtime_error(other) {
		}
		~NotPossibleException() throw() {
		}
	};
} // namespace LTEngine

#endif
