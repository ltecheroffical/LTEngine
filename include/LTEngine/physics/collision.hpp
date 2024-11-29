#ifndef _LTENGINE_PHYSICS_COLLISION_HPP_
#define _LTENGINE_PHYSICS_COLLISION_HPP_

#include <LTEngine/shapes/circle.hpp>
#include <LTEngine/shapes/rect.hpp>


namespace LTEngine::Physics {
	bool isRectColliding(Shapes::Rect a, Shapes::Rect b);
	bool isCircleColliding(Shapes::Circle circleA, Shapes::Circle circleB);
} // namespace LTEngine::Physics

#endif
