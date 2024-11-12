#pragma once

#include <LTEngine/common/types/inttypes.h>

#include <LTEngine/math/vec2.hpp>

#include <LTEngine/shapes/rect.hpp>
#include <LTEngine/shapes/circle.hpp>
#include <LTEngine/shapes/polygon.hpp>
#include <LTEngine/shapes/triangle.hpp>


namespace LTEngine::Physics
{
    class PhysicsEngine
    {
    // It actually quite hard to create a base class for all physics engines
    public:
        virtual ~PhysicsEngine() = default;

        enum class BodyType {
            BODY_TYPE_STATIC = 0,
            BODY_TYPE_KINEMATIC = 1,
            BODY_TYPE_DYNAMIC = 2
        };

        virtual void update(f32 timeStep) = 0;

        virtual void setGravity(const Math::Vec2& gravity) = 0;
        virtual Math::Vec2 getGravity() const = 0;

        virtual u32 addBody(Shapes::Rect rect, BodyType bodyType) = 0;
        virtual u32 addBody(Shapes::Circle circle, BodyType bodyType) = 0;
        virtual u32 addBody(Shapes::Polygon polygon, BodyType bodyType) = 0;
        virtual u32 addBody(Shapes::Triangle triangle, BodyType bodyType) = 0;

        virtual void removeBody(u32 id) = 0;

        virtual void setBodyPosition(u32 id, const Math::Vec2 &position) = 0;
        virtual void setBodyRotation(u32 id, f32 rotation) = 0;

        virtual Math::Vec2 getBodyPosition(u32 id) = 0;
        virtual f32 getBodyRotation(u32 id) = 0;
    };
}
