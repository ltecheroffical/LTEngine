#ifdef LTCORE_COMPONENT_C_API
#include <LTCore/c_api/random/unix_random.h>
#include <LTCore/random/unix_random.hpp>


using namespace LTCore;
using namespace LTCore::Random;


LTCore_HUnixRandom LTCORE_API LTCore_UnixRandom() {
	return {{ new UnixRandom() }};
}

LTCore_HUnixRandom LTCORE_API LTCore_UnixRandom_bufSize(size_t bufferSize) {
	return {{ new UnixRandom(bufferSize) }};
}

#endif
