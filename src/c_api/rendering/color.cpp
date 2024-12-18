#include <LTEngine/c_api/rendering/color.h>

#include <LTEngine/rendering/color.hpp>


LTEngine_HColor LTENGINE_API LTEngine_CreateColor(LTEngine_u8 r, LTEngine_u8 g, LTEngine_u8 b) {
	return new LTEngine::Rendering::Color(r, g, b);
}
