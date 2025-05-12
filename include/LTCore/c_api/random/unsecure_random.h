#ifndef _LTCORE_C_API_RANDOM_UNSECURE_RANDOM_H_
#ifdef LTCORE_COMPONENT_C_API
#define _LTCORE_C_API_RANDOM_UNSECURE_RANDOM_H_

#include <LTCore/c_api/random/random.h>


#ifndef __cplusplus
extern "C" {
#endif

// This handle is compatible with HRandom handle and can be used with HRandom function
typedef LTCore_HRandom LTCore_HUnsecureRandom;


LTCore_HUnsecureRandom LTCORE_API LTCore_UnsecureRandom();

void LTCORE_API LTCore_UnsecureRandom_seed(LTCore_HUnsecureRandom handle, LTCore_u64 seed);

#ifndef __cplusplus
}
#endif
#endif
#endif
