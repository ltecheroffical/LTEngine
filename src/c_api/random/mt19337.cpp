#include <LTEngine/c_api/random/mt19937.h>
#include <LTEngine/random/mt19937.hpp>


using namespace LTEngine;
using namespace LTEngine::Random;


LTEngine_HMT19937 LTEngine_MT19937() {
	return {{new MT19937() }};
}
