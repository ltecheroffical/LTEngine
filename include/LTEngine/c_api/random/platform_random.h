#ifndef _LTENGINE_C_API_RANDOM_PLATFORM_RANDOM_H_
#ifdef LTENGINE_COMPONENT_C_API
#define _LTENGINE_C_API_RANDOM_PLATFORM_RANDOM_H_

#include <LTEngine/c_api/random/random.h>


#ifdef __cplusplus
extern "C" {
#endif


typedef struct LTENGINE_API {
	size_t unix_random_buffer_size;
} LTEngine_PlatformRandom_RandomSettings;

// This handle is compatible with HRandom handle and can be used with HRandom function
typedef LTEngine_HRandom LTEngine_HPlatformRandom;


LTEngine_PlatformRandom_RandomSettings LTENGINE_API LTEngine_PlatformRandom_RandomSettings_createDefault();

LTEngine_HPlatformRandom LTENGINE_API LTEngine_PlatformRandom(LTEngine_PlatformRandom_RandomSettings settings);

#ifdef __cplusplus
}
#endif
#endif
#endif
