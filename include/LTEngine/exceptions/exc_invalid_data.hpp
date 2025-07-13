#ifndef _LTENGINE_EXC_INVALID_DATA_HPP_
#define _LTENGINE_EXC_INVALID_DATA_HPP_

#include <stdexcept>


namespace LTEngine {
	struct InvalidDataException : public std::runtime_error {
		InvalidDataException(std::string message) throw() : std::runtime_error(message) {
		}
		InvalidDataException(const InvalidDataException &other) throw() : std::runtime_error(other) {
		}
		~InvalidDataException() throw() {
		}
	};
} // namespace LTEngine

#endif
