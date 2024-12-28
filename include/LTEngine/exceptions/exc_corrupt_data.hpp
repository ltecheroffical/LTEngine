#ifndef _LTENGINE_EXC_CORRUPT_DATA_HPP_
#define _LTENGINE_EXC_CORRUPT_DATA_HPP_

#include <LTEngine/exceptions/exc_invalid_data.hpp>

namespace LTEngine {
	class CorruptDataException : public InvalidDataException {
	public:
		CorruptDataException(std::string message) throw() : InvalidDataException(message) {
		}
		CorruptDataException(const CorruptDataException &other) throw() : InvalidDataException(other) {
		}
		~CorruptDataException() throw() {
		}
	};
} // namespace LTEngine

#endif
