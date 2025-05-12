#ifndef _LTCORE_EXC_CORRUPT_DATA_HPP_
#define _LTCORE_EXC_CORRUPT_DATA_HPP_

#include <LTCore/exceptions/exc_invalid_data.hpp>

namespace LTCore {
	class CorruptDataException : public InvalidDataException {
	public:
		CorruptDataException(std::string message) throw() : InvalidDataException(message) {
		}
		CorruptDataException(const CorruptDataException &other) throw() : InvalidDataException(other) {
		}
		~CorruptDataException() throw() {
		}
	};
} // namespace LTCore

#endif
