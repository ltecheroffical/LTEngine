#ifdef LTENGINE_COMPONENT_C_API
#include <LTEngine/c_api/random/platform_random.h>
#include <LTEngine/random/platform_random.hpp>


using namespace LTEngine;
using namespace LTEngine::Random;


LTEngine_PlatformRandom_RandomSettings LTEngine_PlatformRandom_RandomSettings_createDefault() {
	LTEngine_PlatformRandom_RandomSettings settings;
	settings.unix_random_buffer_size = 512;
	return settings;
}


LTEngine_HPlatformRandom LTEngine_PlatformRandom(LTEngine_PlatformRandom_RandomSettings settings) {
	return {{new PlatformRandom({.unixRandomBufferSize = settings.unix_random_buffer_size})}};
}

#endif
