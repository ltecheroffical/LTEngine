#ifndef _LTENGINE_C_API_RANDOM_UNIX_RANDOM_H_
#define _LTENGINE_C_API_RANDOM_UNIX_RANDOM_H_

#include <LTEngine/c_api/random/random.h>


#ifndef __cplusplus
extern "C" {
#endif


// This handle is compatible with HRandom handle and can be used with HRandom function
typedef LTEngine_HRandom LTEngine_HUnixRandom;


LTEngine_HUnixRandom LTENGINE_API LTEngine_UnixRandom();
LTEngine_HUnixRandom LTENGINE_API LTEngine_UnixRandom_bufSize(size_t bufferSize);

#ifndef __cplusplus
}
#endif
#endif
