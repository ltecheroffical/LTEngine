#include <LTEngine/physics/box2d.hpp>


using namespace LTEngine;
using namespace LTEngine::Physics;


const f32 PIXELS_PER_METER = 50.f;
const f32 METERS_PER_PIXEL = 1.f / PIXELS_PER_METER;


Box2D::Box2D() {
    b2WorldDef worldDef = b2DefaultWorldDef();

    worldDef.gravity = b2Vec2(0.0f, 0.0f);

    b2WorldId worldId = b2CreateWorld(&worldDef);
    m_world = worldId;
}

Box2D::~Box2D() {
    m_bodies.clear();
    m_bodySizes.clear();
    b2DestroyWorld(m_world);
}


void Box2D::update(f32 timeStep) {
    b2World_Step(m_world, timeStep, 4);
}


void Box2D::setGravity(const Math::Vec2& gravity) {
    b2World_SetGravity(m_world, b2Vec2(gravity.x, gravity.y));
}

Math::Vec2 Box2D::getGravity() const {
    return Math::Vec2(b2World_GetGravity(m_world).x, b2World_GetGravity(m_world).y);
}


u32 Box2D::addBody(Shapes::Rect rect, PhysicsEngine::BodyType bodyType) {
    b2BodyDef bodyDef = b2DefaultBodyDef();

    switch (bodyType) {
        default:
        case PhysicsEngine::BodyType::BODY_TYPE_STATIC:
            bodyDef.type = b2_staticBody;
            break;
        case PhysicsEngine::BodyType::BODY_TYPE_DYNAMIC:
            bodyDef.type = b2_dynamicBody;
            break;
        case PhysicsEngine::BodyType::BODY_TYPE_KINEMATIC:
            bodyDef.type = b2_kinematicBody;
            break;
    }

    bodyDef.position = b2Vec2(
        (rect.x + rect.w) * METERS_PER_PIXEL,
        (rect.y + rect.h) * METERS_PER_PIXEL
    );
    bodyDef.rotation = b2MakeRot(rect.rotation);


    b2BodyId bodyId = b2CreateBody(m_world, &bodyDef);
    b2Polygon shape = b2MakeBox(rect.w * METERS_PER_PIXEL, rect.h * METERS_PER_PIXEL);

    b2ShapeDef shapeDef = b2DefaultShapeDef();
    b2CreatePolygonShape(bodyId, &shapeDef, &shape);

    u32 id = m_nextId++;
    m_bodies[id] = bodyId;
    m_bodySizes[id] = b2Vec2(rect.w, rect.h);
    return id;
}

u32 Box2D::addBody(Shapes::Circle circle, PhysicsEngine::BodyType bodyType) {
    b2BodyDef bodyDef = b2DefaultBodyDef();

    switch (bodyType) {
        default:
        case PhysicsEngine::BodyType::BODY_TYPE_STATIC:
            bodyDef.type = b2_staticBody;
            break;
        case PhysicsEngine::BodyType::BODY_TYPE_DYNAMIC:
            bodyDef.type = b2_dynamicBody;
            break;
        case PhysicsEngine::BodyType::BODY_TYPE_KINEMATIC:
            bodyDef.type = b2_kinematicBody;
            break;
    }

    bodyDef.position = b2Vec2(circle.x * METERS_PER_PIXEL, circle.y * METERS_PER_PIXEL);
    bodyDef.rotation = b2MakeRot(circle.rotation);

    b2BodyId bodyId = b2CreateBody(m_world, &bodyDef);

    b2Circle shape;
    shape.radius = circle.radius * METERS_PER_PIXEL;
    shape.center = b2Vec2(circle.x * METERS_PER_PIXEL, circle.y * METERS_PER_PIXEL);

    b2ShapeDef shapeDef = b2DefaultShapeDef();
    b2CreateCircleShape(bodyId, &shapeDef, &shape);

    u32 id = m_nextId++;
    m_bodies[id] = bodyId;
    return id;
}

u32 Box2D::addBody(Shapes::Polygon polygon, PhysicsEngine::BodyType bodyType) {
    b2BodyDef bodyDef = b2DefaultBodyDef();

    switch (bodyType) {
        default:
        case PhysicsEngine::BodyType::BODY_TYPE_STATIC:
            bodyDef.type = b2_staticBody;
            break;
        case PhysicsEngine::BodyType::BODY_TYPE_DYNAMIC:
            bodyDef.type = b2_dynamicBody;
            break;
        case PhysicsEngine::BodyType::BODY_TYPE_KINEMATIC:
            bodyDef.type = b2_kinematicBody;
            break;
    }

    bodyDef.position = b2Vec2(polygon.x * METERS_PER_PIXEL, polygon.y * METERS_PER_PIXEL);
    bodyDef.rotation = b2MakeRot(polygon.rotation);

    b2BodyId bodyId = b2CreateBody(m_world, &bodyDef);
    
    std::vector<b2Vec2> points;
    for (Math::Vec2 point : polygon.points) {
        points.push_back(b2Vec2(point.x * METERS_PER_PIXEL, point.y * METERS_PER_PIXEL));
    }
    b2Hull hull = b2ComputeHull(points.data(), points.size());

    const f32 radius = 0.1f; // Box2D, why is this a requirement?
    b2Polygon shape = b2MakePolygon(&hull, radius);

    b2ShapeDef shapeDef = b2DefaultShapeDef();
    b2CreatePolygonShape(bodyId, &shapeDef, &shape);

    u32 id = m_nextId++;
    m_bodies[id] = bodyId;
    return id;
}

u32 Box2D::addBody(Shapes::Triangle triangle, PhysicsEngine::BodyType bodyType) {
    b2BodyDef bodyDef = b2DefaultBodyDef();

    switch (bodyType) {
        default:
        case PhysicsEngine::BodyType::BODY_TYPE_STATIC:
            bodyDef.type = b2_staticBody;
            break;
        case PhysicsEngine::BodyType::BODY_TYPE_DYNAMIC:
            bodyDef.type = b2_dynamicBody;
            break;
        case PhysicsEngine::BodyType::BODY_TYPE_KINEMATIC:
            bodyDef.type = b2_kinematicBody;
            break;
    }

    bodyDef.position = b2Vec2(triangle.x * METERS_PER_PIXEL, triangle.y * METERS_PER_PIXEL);
    bodyDef.rotation = b2MakeRot(triangle.rotation);

    b2BodyId bodyId = b2CreateBody(m_world, &bodyDef);
    
    b2Vec2 points[3] = {
        b2Vec2(triangle.p1.x * METERS_PER_PIXEL, triangle.p1.y * METERS_PER_PIXEL),
        b2Vec2(triangle.p2.x * METERS_PER_PIXEL, triangle.p2.y * METERS_PER_PIXEL),
        b2Vec2(triangle.p3.x * METERS_PER_PIXEL, triangle.p3.y * METERS_PER_PIXEL)
    };
    b2Hull hull = b2ComputeHull(points, 3);

    const f32 radius = 0.1f; // Box2D, why is this a requirement?
    b2Polygon shape = b2MakePolygon(&hull, radius);

    b2ShapeDef shapeDef = b2DefaultShapeDef();
    b2CreatePolygonShape(bodyId, &shapeDef, &shape);

    u32 id = m_nextId++;
    m_bodies[id] = bodyId;
    return id;
}


void Box2D::removeBody(u32 id) {
    if (!m_bodies.contains(id)) {
        return;
    }
    b2DestroyBody(m_bodies.at(id));
    m_bodies.erase(id);
    m_bodySizes.erase(id);
}


void Box2D::setBodyPosition(u32 id, const Math::Vec2 &position) {
    b2Body_SetTransform(m_bodies[id], b2Vec2(position.x * METERS_PER_PIXEL, position.y * METERS_PER_PIXEL), b2Body_GetRotation(m_bodies[id]));
}

void Box2D::setBodyRotation(u32 id, f32 rotation) {
    b2Body_SetTransform(m_bodies[id], b2Body_GetPosition(m_bodies[id]), b2MakeRot(rotation));
}


Math::Vec2 Box2D::getBodyPosition(u32 id) {
    b2Vec2 position = b2Body_GetPosition(m_bodies[id]);
    return Math::Vec2(position.x * PIXELS_PER_METER - (m_bodySizes[id].x), position.y * PIXELS_PER_METER - (m_bodySizes[id].y));
}

f32 Box2D::getBodyRotation(u32 id) {
    return b2Rot_GetAngle(b2Body_GetRotation(m_bodies[id]));
}
