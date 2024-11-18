#ifndef _LTENGINE_COMPILER_UTILS_H_
#define _LTENGINE_COMPILER_UTILS_H_

#if defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__) || defined(__GNU__) || defined(__clang__)
#define LTENGINE_PACK_START() _Pragma("pack(1)")
#define LTENGINE_PACK_END()                                                                                                        \
	;                                                                                                                              \
	_Pragma("pack()")
#else
#warning "This compiler doesn't support packing, there may be compatibility issues."
#endif

#endif
