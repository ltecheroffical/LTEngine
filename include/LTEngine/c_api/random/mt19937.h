#ifndef _LTENGINE_C_API_RANDOM_MT19937_H_
#define _LTENGINE_C_API_RANDOM_MT19937_H_

#include <LTEngine/c_api/random/random.h>


#ifndef __cplusplus
extern "C" {
#endif


// This handle is compatible with HRandom handle and can be used with HRandom function
typedef LTEngine_HRandom LTEngine_HMT19937;


LTEngine_HMT19937 LTENGINE_API LTEngine_MT19937_init();

#ifndef __cplusplus
}
#endif
#endif
