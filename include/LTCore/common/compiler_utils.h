#ifndef _LTCORE_COMPILER_UTILS_H_
#define _LTCORE_COMPILER_UTILS_H_

#include <LTCore/common/types/floattypes.h>
#include <LTCore/common/types/inttypes.h>

#ifdef __cplusplus
// Fixing issues with some compilers that don't include these with other std headers
// My (@ltecheroffical) compiler does include these with std headers
#include <algorithm>
#include <cstring>
#include <memory>
#include <stdexcept>
#else
#include <stdbool.h>
#endif

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)


#if defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__) || defined(__GNU__) || defined(__GNUC__) || defined(__clang__)
#define LTCORE_PACK_START() _Pragma("pack(push, 1)")
#define LTCORE_PACK_CUSTOM_START(x) _Pragma(TOSTRING(pack(push, x)))
#define LTCORE_PACK_END()                                                                                                        \
	;                                                                                                                              \
	_Pragma("pack(pop)")
#else
#warning "This compiler doesn't support packing, there may be compatibility issues."
#define LTCORE_PACK_START()
#define LTCORE_PACK_END()
#define LTCORE_COMPILER_DATA_COMPATIBILITY_ISSUE
#endif

#ifdef _WIN32
#ifdef LTCORE_SHARED
#define LTCORE_API __declspec(dllexport)
#else
#define LTCORE_API __declspec(dllimport)
#endif
#else
#define LTCORE_API __attribute__((visibility("default")))
#endif

#ifdef LTCORE_COMPILER_DATA_COMPATIBILITY_ISSUE
#warning "This compiler has some data compatibility issues, a few features will be disabled."
#endif

#endif
