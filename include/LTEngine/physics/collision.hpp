#ifndef _LTENGINE_PHYSICS_COLLISION_HPP_
#define _LTENGINE_PHYSICS_COLLISION_HPP_

#include <LTEngine/shapes/circle.hpp>
#include <LTEngine/shapes/polygon.hpp>
#include <LTEngine/shapes/rect.hpp>
#include <LTEngine/shapes/triangle.hpp>


namespace LTEngine::Physics {
	bool testCollision(Shapes::Rect a, Shapes::Rect b);
	bool testCollision(Shapes::Rect a, Shapes::Circle b);
	bool testCollision(Shapes::Rect a, Shapes::Polygon b);
	bool testCollision(Shapes::Rect a, Shapes::Triangle b);

	bool testCollision(Shapes::Circle a, Shapes::Circle b);
	bool testCollision(Shapes::Circle a, Shapes::Rect b);
	bool testCollision(Shapes::Circle a, Shapes::Polygon b);
	bool testCollision(Shapes::Circle a, Shapes::Triangle b);

	bool testCollision(Shapes::Polygon a, Shapes::Polygon b);
	bool testCollision(Shapes::Polygon a, Shapes::Rect b);
	bool testCollision(Shapes::Polygon a, Shapes::Circle b);
	bool testCollision(Shapes::Polygon a, Shapes::Triangle b);

	bool testCollision(Shapes::Triangle a, Shapes::Triangle b);
	bool testCollision(Shapes::Triangle a, Shapes::Rect b);
	bool testCollision(Shapes::Triangle a, Shapes::Circle b);
	bool testCollision(Shapes::Triangle a, Shapes::Polygon b);
} // namespace LTEngine::Physics

#endif
