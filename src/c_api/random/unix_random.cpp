#ifdef LTENGINE_COMPONENT_C_API
#include <LTEngine/c_api/random/unix_random.h>
#include <LTEngine/random/unix_random.hpp>


using namespace LTEngine;
using namespace LTEngine::Random;


LTEngine_HUnixRandom LTENGINE_API lt_engine_unix_random() {
	return {{ new UnixRandom() }};
}

LTEngine_HUnixRandom LTENGINE_API lt_engine_unix_random_buf_size(size_t buffer_size) {
	return {{ new UnixRandom(buffer_size) }};
}

#endif
