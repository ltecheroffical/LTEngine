#ifdef LTCORE_COMPONENT_C_API
#include <LTCore/c_api/random/platform_random.h>
#include <LTCore/random/platform_random.hpp>


using namespace LTCore;
using namespace LTCore::Random;


LTCore_PlatformRandom_RandomSettings LTCore_PlatformRandom_RandomSettings_createDefault() {
	LTCore_PlatformRandom_RandomSettings settings;
	settings.unix_random_buffer_size = 512;
	return settings;
}


LTCore_HPlatformRandom LTCore_PlatformRandom(LTCore_PlatformRandom_RandomSettings settings) {
	return {{new PlatformRandom({.unixRandomBufferSize = settings.unix_random_buffer_size})}};
}

#endif
