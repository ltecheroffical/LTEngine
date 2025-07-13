#ifndef _LTENGINE_EXC_NOT_FOUND_
#define _LTENGINE_EXC_NOT_FOUND_

#include <stdexcept>

namespace LTEngine {
	class NotFoundException : public std::runtime_error {
	public:
		NotFoundException(const std::string &message) : std::runtime_error(message) {
		}
		NotFoundException(const NotFoundException &other) : std::runtime_error(other) {
		}
		~NotFoundException() throw() {
		}
	};
} // namespace LTEngine

#endif
