#ifdef LTENGINE_COMPONENT_C_API
#include <LTEngine/c_api/random/platform_random.h>
#include <LTEngine/random/platform_random.hpp>


using namespace LTEngine;
using namespace LTEngine::Random;


LTEngine_PlatformRandom_RandomSettings lt_engine_platform_random_random_settings_create_default() {
	LTEngine_PlatformRandom_RandomSettings settings;
	settings.unix_random_buffer_size = 512;
	return settings;
}


LTEngine_HPlatformRandom lt_engine_platform_random(LTEngine_PlatformRandom_RandomSettings settings) {
	return {{new PlatformRandom({.unix_random_buffer_size = settings.unix_random_buffer_size})}};
}

#endif
