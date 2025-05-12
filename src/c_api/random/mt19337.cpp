#ifdef LTCORE_COMPONENT_C_API
#include <LTCore/c_api/random/mt19937.h>
#include <LTCore/random/mt19937.hpp>


using namespace LTCore;
using namespace LTCore::Random;


LTCore_HMT19937 LTCore_MT19937() {
	return {{new MT19937() }};
}

#endif
