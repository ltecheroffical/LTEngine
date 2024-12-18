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

#if defined(__GNU__) || defined(__clang__)
#define LTENGINE_WARN_UNUSED_RESULT __attribute__((warn_unused_result))

#define LTENGINE_UNUSED __attribute__((unused))
#else
#define LTENGINE_WARN_UNUSED_RESULT

#define LTENGINE_UNUSED
#endif

#ifdef _WIN32
#ifdef LTENGINE_SHARED
#define LTENGINE_API __declspec(dllexport)
#else
#define LTENGINE_API __declspec(dllimport)
#endif
#else
#define LTENGINE_API __attribute__((visibility("default")))
#endif

#endif
