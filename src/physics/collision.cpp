#include <LTEngine/physics/collision.hpp>


using namespace LTEngine;


bool Physics::isRectColliding(Math::Rect a, Math::Rect b) {
    return a.x < b.x + b.w && a.x + a.w > b.x && a.y < b.y + b.h && a.y + a.h > b.y;
}

bool Physics::isCircleColliding(Math::Vec2 centerA, f32 radiusA, Math::Vec2 centerB, f32 radiusB) {
    return (centerA.x - centerB.x) * (centerA.x - centerB.x) + (centerA.y - centerB.y) * (centerA.y - centerB.y) < (radiusA + radiusB) * (radiusA + radiusB);
}
