#ifndef _LTCORE_PHYSICS_COLLISION_HPP_
#define _LTCORE_PHYSICS_COLLISION_HPP_

#include <LTCore/shapes/2d/circle.hpp>
#include <LTCore/shapes/2d/polygon.hpp>
#include <LTCore/shapes/2d/rect.hpp>
#include <LTCore/shapes/2d/triangle.hpp>


namespace LTCore::Physics {
	bool LTCORE_API testCollision(Shapes::Rect a, Shapes::Rect b);
	bool LTCORE_API testCollision(Shapes::Rect a, Shapes::Circle b);
	bool LTCORE_API testCollision(Shapes::Rect a, Shapes::Polygon b);
	bool LTCORE_API testCollision(Shapes::Rect a, Shapes::Triangle b);

	bool LTCORE_API testCollision(Shapes::Circle a, Shapes::Circle b);
	bool LTCORE_API testCollision(Shapes::Circle a, Shapes::Rect b);
	bool LTCORE_API testCollision(Shapes::Circle a, Shapes::Polygon b);
	bool LTCORE_API testCollision(Shapes::Circle a, Shapes::Triangle b);

	bool LTCORE_API testCollision(Shapes::Polygon a, Shapes::Polygon b);
	bool LTCORE_API testCollision(Shapes::Polygon a, Shapes::Rect b);
	bool LTCORE_API testCollision(Shapes::Polygon a, Shapes::Circle b);
	bool LTCORE_API testCollision(Shapes::Polygon a, Shapes::Triangle b);

	bool LTCORE_API testCollision(Shapes::Triangle a, Shapes::Triangle b);
	bool LTCORE_API testCollision(Shapes::Triangle a, Shapes::Rect b);
	bool LTCORE_API testCollision(Shapes::Triangle a, Shapes::Circle b);
	bool LTCORE_API testCollision(Shapes::Triangle a, Shapes::Polygon b);
} // namespace LTCore::Physics

#endif
