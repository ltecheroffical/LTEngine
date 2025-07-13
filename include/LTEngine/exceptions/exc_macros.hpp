#ifndef _LTENGINE_EXC_MACROS_HPP_
#define _LTENGINE_EXC_MACROS_HPP_

#include <exception>

#define LTENGINE_CREATE_EXCEPTION(name)                       \
	class name : std::exception {                             \
	  public:                                                 \
		name(std::string message) : std::exception(message) { \
		}                                                     \
		name(const name &other) : std::exception(message) {   \
		}                                                     \
		~name() : throw() {                                   \
		}                                                     \
	}

#define LTENGINE_CREATE_EXCEPTION_WITH_BASE(name, base) \
	class name : base {                                 \
	  public:                                           \
		name(std::string message) : base(message) {     \
		}                                               \
		name(const name &other) : base(message) {       \
		}                                               \
		~name() : throw() {                             \
		}                                               \
	}

#endif // _LTENGINE_EXC_MACROS_HPP_
