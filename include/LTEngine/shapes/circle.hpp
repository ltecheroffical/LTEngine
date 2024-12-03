#ifndef _LTENGINE_SHAPES_CIRCLE_HPP_
#define _LTENGINE_SHAPES_CIRCLE_HPP_

#include <LTEngine/math/vec2.hpp>

#include <LTEngine/shapes/shape.hpp>

#include <LTEngine/common/compiler_utils.h>


namespace LTEngine::Shapes {
	struct LTENGINE_API Circle : public Shape {
		f32 radius;
	};
} // namespace LTEngine::Shapes

#endif
