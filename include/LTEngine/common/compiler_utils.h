#ifndef _LTENGINE_COMPILER_UTILS_H_
#define _LTENGINE_COMPILER_UTILS_H_

#include <LTEngine/common/types/floattypes.h>
#include <LTEngine/common/types/inttypes.h>

#ifdef __cplusplus
// Fixing issues with some compilers that don't include these with other std headers
// My (@ltecheroffical) compiler does include these with std headers
#include <cstring>
#include <memory>
#include <stdexcept>
#endif


#if defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__) || defined(__GNU__) || defined(__clang__)
#define LTENGINE_PACK_START() _Pragma("pack(push, 1)")
#define LTENGINE_PACK_END()                                                                                                        \
	;                                                                                                                              \
	_Pragma("pack(pop)")
#else
#warning "This compiler doesn't support packing, there may be compatibility issues."
#define LTENGINE_PACK_START()
#define LTENGINE_PACK_END()
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
