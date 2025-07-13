#ifndef _LTENGINE_C_API_RANDOM_UNIX_RANDOM_H_I
#ifdef LTENGINE_COMPONENT_C_API
#define _LTENGINE_C_API_RANDOM_UNIX_RANDOM_H_

#include <LTEngine/c_api/random/random.h>


#ifndef __cplusplus
extern "C" {
#endif


// This handle is compatible with HRandom handle and can be used with HRandom function
typedef LTEngine_HRandom LTEngine_HUnixRandom;


LTEngine_HUnixRandom LTENGINE_API lt_engine_unix_random();
LTEngine_HUnixRandom LTENGINE_API lt_engine_unix_random_buf_size(size_t buffer_size);

#ifndef __cplusplus
}
#endif
#endif
#endif
