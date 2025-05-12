#ifndef _LTCORE_C_API_RANDOM_PLATFORM_RANDOM_H_
#ifdef LTCORE_COMPONENT_C_API
#define _LTCORE_C_API_RANDOM_PLATFORM_RANDOM_H_

#include <LTCore/c_api/random/random.h>


#ifdef __cplusplus
extern "C" {
#endif


typedef struct LTCORE_API {
	size_t unix_random_buffer_size;
} LTCore_PlatformRandom_RandomSettings;

// This handle is compatible with HRandom handle and can be used with HRandom function
typedef LTCore_HRandom LTCore_HPlatformRandom;


LTCore_PlatformRandom_RandomSettings LTCORE_API LTCore_PlatformRandom_RandomSettings_createDefault();

LTCore_HPlatformRandom LTCORE_API LTCore_PlatformRandom(LTCore_PlatformRandom_RandomSettings settings);

#ifdef __cplusplus
}
#endif
#endif
#endif
