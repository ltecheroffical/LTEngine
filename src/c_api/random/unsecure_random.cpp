#ifdef LTENGINE_COMPONENT_C_API
#include <LTEngine/c_api/random/unsecure_random.h>
#include <LTEngine/random/unsecure_random.hpp>


using namespace LTEngine;
using namespace LTEngine::Random;


LTEngine_HUnsecureRandom LTENGINE_API lt_engine_unsecure_random() {
	return {{ new RandomUnsecure() }};
}


void LTENGINE_API lt_engine_unsecure_random_seed(LTEngine_HUnsecureRandom handle, LTEngine_u64 seed) {
	((RandomUnsecure *)handle.handle.ptr)->seed(seed);
}

#endif
