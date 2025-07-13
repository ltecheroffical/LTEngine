#include <LTEngine/physics/collision_2d.hpp>


using namespace LTEngine;


bool Physics::test_collision(Shapes::Rect a, Shapes::Rect b) {
	if (a.x + a.w <= b.x || b.x + b.w <= a.x) return false;
	if (a.y + a.h <= b.y || b.y + b.h <= a.y) return false;
	return true;
}

bool Physics::test_collision(Shapes::Circle circle_a, Shapes::Circle circle_b) {
	return (circle_a.x - circle_b.x) * (circle_a.x - circle_b.x) + (circle_a.y - circle_b.y) * (circle_a.y - circle_b.y) <
	       (circle_a.radius + circle_b.radius) * (circle_a.radius + circle_b.radius);
}
