#ifndef _LTENGINE_SHAPE_2D_CIRCLE_HPP_
#define _LTENGINE_SHAPE_2D_CIRCLE_HPP_

#include <LTEngine/math/vec2.hpp>

#include <LTEngine/shapes/2d/shape.hpp>


namespace LTEngine::Shapes {
	struct Circle : public Shape2D {
		f32 radius;
	};
} // namespace LTEngine::Shapes

#endif
