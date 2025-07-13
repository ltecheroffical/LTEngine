#ifndef _LTENGINE_C_API_RANDOM_UNSECURE_RANDOM_H_
#ifdef LTENGINE_COMPONENT_C_API
#define _LTENGINE_C_API_RANDOM_UNSECURE_RANDOM_H_

#include <LTEngine/c_api/random/random.h>


#ifndef __cplusplus
extern "C" {
#endif

// This handle is compatible with HRandom handle and can be used with HRandom function
typedef LTEngine_HRandom LTEngine_HUnsecureRandom;


LTEngine_HUnsecureRandom LTENGINE_API LTEngine_UnsecureRandom();

void LTENGINE_API LTEngine_UnsecureRandom_seed(LTEngine_HUnsecureRandom handle, LTEngine_u64 seed);

#ifndef __cplusplus
}
#endif
#endif
#endif
