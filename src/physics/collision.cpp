#include <LTEngine/physics/collision.hpp>


using namespace LTEngine;


bool Physics::testCollision(Shapes::Rect a, Shapes::Rect b) {
	if (a.x + a.w <= b.x || b.x + b.w <= a.x) return false;
	if (a.y + a.h <= b.y || b.y + b.h <= a.y) return false;
	return true;
}

bool Physics::testCollision(Shapes::Circle circleA, Shapes::Circle circleB) {
	return (circleA.x - circleB.x) * (circleA.x - circleB.x) + (circleA.y - circleB.y) * (circleA.y - circleB.y) <
	       (circleA.radius + circleB.radius) * (circleA.radius + circleB.radius);
}
