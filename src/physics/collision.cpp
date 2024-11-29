#include <LTEngine/physics/collision.hpp>


using namespace LTEngine;


bool Physics::isRectColliding(Shapes::Rect a, Shapes::Rect b) {
	return a.x < b.x + b.w && a.x + a.w > b.x && a.y < b.y + b.h && a.y + a.h > b.y;
}

bool Physics::isCircleColliding(Shapes::Circle circleA, Shapes::Circle circleB) {
	return (circleA.x - circleB.x) * (circleA.x - circleB.x) + (circleA.y - circleB.y) * (circleA.y - circleB.y) <
	       (circleA.radius + circleB.radius) * (circleA.radius + circleB.radius);
}
