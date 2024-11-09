#pragma once

#include <LTEngine/math/rect.hpp>


namespace LTEngine::Physics {
    bool isRectColliding(Math::Rect a, Math::Rect b);
    bool isCircleColliding(Math::Vec2 centerA, f32 radiusA, Math::Vec2 centerB, f32 radiusB);
}
