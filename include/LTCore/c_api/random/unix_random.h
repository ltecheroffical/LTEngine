#ifndef _LTCORE_C_API_RANDOM_UNIX_RANDOM_H_I
#ifdef LTCORE_COMPONENT_C_API
#define _LTCORE_C_API_RANDOM_UNIX_RANDOM_H_

#include <LTCore/c_api/random/random.h>


#ifndef __cplusplus
extern "C" {
#endif


// This handle is compatible with HRandom handle and can be used with HRandom function
typedef LTCore_HRandom LTCore_HUnixRandom;


LTCore_HUnixRandom LTCORE_API LTCore_UnixRandom();
LTCore_HUnixRandom LTCORE_API LTCore_UnixRandom_bufSize(size_t bufferSize);

#ifndef __cplusplus
}
#endif
#endif
#endif
