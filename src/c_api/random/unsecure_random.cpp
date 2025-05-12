#ifdef LTCORE_COMPONENT_C_API
#include <LTCore/c_api/random/unsecure_random.h>
#include <LTCore/random/unsecure_random.hpp>


using namespace LTCore;
using namespace LTCore::Random;


LTCore_HUnsecureRandom LTCORE_API LTCore_UnsecureRandom() {
	return {{ new RandomUnsecure() }};
}


void LTCORE_API LTCore_UnsecureRandom_seed(LTCore_HUnsecureRandom handle, LTCore_u64 seed) {
	((RandomUnsecure *)handle.handle.ptr)->seed(seed);
}

#endif
