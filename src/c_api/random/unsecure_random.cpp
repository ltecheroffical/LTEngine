#ifdef LTENGINE_COMPONENT_C_API
#include <LTEngine/c_api/random/unsecure_random.h>
#include <LTEngine/random/unsecure_random.hpp>


using namespace LTEngine;
using namespace LTEngine::Random;


LTEngine_HUnsecureRandom LTENGINE_API LTEngine_UnsecureRandom() {
	return {{ new RandomUnsecure() }};
}


void LTENGINE_API LTEngine_UnsecureRandom_seed(LTEngine_HUnsecureRandom handle, LTEngine_u64 seed) {
	((RandomUnsecure *)handle.handle.ptr)->seed(seed);
}

#endif
