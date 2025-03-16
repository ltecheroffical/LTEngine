#include <LTEngine/c_api/random/unix_random.h>
#include <LTEngine/random/unix_random.hpp>


using namespace LTEngine;
using namespace LTEngine::Random;


LTEngine_HUnixRandom LTENGINE_API LTEngine_UnixRandom() {
	return {{ new UnixRandom() }};
}

LTEngine_HUnixRandom LTENGINE_API LTEngine_UnixRandom_bufSize(size_t bufferSize) {
	return {{ new UnixRandom(bufferSize) }};
}
