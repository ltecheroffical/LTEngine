#include <LTEngine/physics/box2d.hpp>


using namespace LTEngine;
using namespace LTEngine::Physics;


const f32 PIXELS_PER_METER = 50.f;
const f32 METERS_PER_PIXEL = 1.f / PIXELS_PER_METER;


Box2D::Box2D() {
	b2WorldDef worldDef = b2DefaultWorldDef();

	worldDef.gravity = b2Vec2{0.f, 0.f};

	b2WorldId worldId = b2CreateWorld(&worldDef);
	m_world = worldId;
}

Box2D::~Box2D() {
	m_bodies.clear();
	m_joints.clear();

	m_bodySizes.clear();
	b2DestroyWorld(m_world);
}


void Box2D::update(f32 timeStep) {
	b2World_Step(m_world, timeStep, 4);
	std::for_each(m_bodies.begin(), m_bodies.end(), [this](std::pair<u32, b2BodyId> pair) {
		b2ContactData contactData[b2Body_GetContactCapacity(pair.second)];
		u32 contactCount = b2Body_GetContactData(pair.second, contactData, b2Body_GetContactCapacity(pair.second));

		for (u32 i = 0; i < contactCount; i++) {
			b2ContactData *contactData = &contactData[i];
			b2BodyId bodyB = b2Shape_GetBody(contactData->shapeIdB);

			auto otherBody = std::find_if(m_bodies.begin(), m_bodies.end(), [bodyB](std::pair<u32, b2BodyId> bodyPair) {
				// We have to compare everything since Box2D doesn't provide an id comparison function
				return bodyB.revision == bodyPair.second.revision && bodyB.index1 == bodyPair.second.index1 &&
				       bodyB.world0 == bodyPair.second.world0;
			});

			onBodyCollision(pair.first, otherBody->first);
		}
	});
}


void Box2D::setGravity(const Math::Vec2 &gravity) {
	b2World_SetGravity(m_world, b2Vec2{gravity.x, gravity.y});
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

	bodyDef.position = b2Vec2{(rect.x + rect.w) * METERS_PER_PIXEL, (rect.y + rect.h) * METERS_PER_PIXEL};
	bodyDef.rotation = b2MakeRot(rect.rotation);


	b2BodyId bodyId = b2CreateBody(m_world, &bodyDef);
	b2Polygon shape = b2MakeBox(rect.w * METERS_PER_PIXEL, rect.h * METERS_PER_PIXEL);

	b2ShapeDef shapeDef = b2DefaultShapeDef();
	b2CreatePolygonShape(bodyId, &shapeDef, &shape);

	u32 id = m_nextId++;
	m_bodies[id] = bodyId;
	m_bodySizes[id] = b2Vec2{(f32)rect.w, (f32)rect.h};
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

	bodyDef.position = b2Vec2{circle.x * METERS_PER_PIXEL, circle.y * METERS_PER_PIXEL};
	bodyDef.rotation = b2MakeRot(circle.rotation);

	b2BodyId bodyId = b2CreateBody(m_world, &bodyDef);

	b2Circle shape;
	shape.radius = circle.radius * METERS_PER_PIXEL;
	shape.center = b2Vec2{circle.x * METERS_PER_PIXEL, circle.y * METERS_PER_PIXEL};

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

	bodyDef.position = b2Vec2{polygon.x * METERS_PER_PIXEL, polygon.y * METERS_PER_PIXEL};
	bodyDef.rotation = b2MakeRot(polygon.rotation);

	b2BodyId bodyId = b2CreateBody(m_world, &bodyDef);

	std::vector<b2Vec2> points;
	for (Math::Vec2 point : polygon.points) { points.push_back(b2Vec2{point.x * METERS_PER_PIXEL, point.y * METERS_PER_PIXEL}); }
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

	bodyDef.position = b2Vec2{triangle.x * METERS_PER_PIXEL, triangle.y * METERS_PER_PIXEL};
	bodyDef.rotation = b2MakeRot(triangle.rotation);

	b2BodyId bodyId = b2CreateBody(m_world, &bodyDef);

	b2Vec2 points[3] = {b2Vec2{triangle.p1.x * METERS_PER_PIXEL, triangle.p1.y * METERS_PER_PIXEL},
	                    b2Vec2{triangle.p2.x * METERS_PER_PIXEL, triangle.p2.y * METERS_PER_PIXEL},
	                    b2Vec2{triangle.p3.x * METERS_PER_PIXEL, triangle.p3.y * METERS_PER_PIXEL}};
	b2Hull hull = b2ComputeHull(points, 3);

	const f32 radius = 0.1f; // Box2D, why is this a requirement?
	b2Polygon shape = b2MakePolygon(&hull, radius);

	b2ShapeDef shapeDef = b2DefaultShapeDef();
	b2CreatePolygonShape(bodyId, &shapeDef, &shape);

	u32 id = m_nextId++;
	m_bodies[id] = bodyId;
	return id;
}

u32 Box2D::addJoint(u32 bodyIdA, u32 bodyIdB, const Math::Vec2 anchorA, const Math::Vec2 anchorB) {
	b2DistanceJointDef jointDef; // What is that type name?
	jointDef.bodyIdA = m_bodies.at(bodyIdA);
	jointDef.bodyIdB = m_bodies.at(bodyIdB);
	jointDef.localAnchorA = b2Vec2{anchorA.x * METERS_PER_PIXEL, anchorA.y * METERS_PER_PIXEL};
	jointDef.localAnchorB = b2Vec2{anchorB.x * METERS_PER_PIXEL, anchorB.y * METERS_PER_PIXEL};

	b2JointId jointId = b2CreateDistanceJoint(m_world, &jointDef);
	u32 id = m_nextId++;
	m_joints[id] = jointId;
	return id;
}


void Box2D::addForce(u32 id, Math::Vec2 force) {
	const bool WAKE_BODY = true;
	b2Body_ApplyForceToCenter(m_bodies.at(id), b2Vec2{force.x, force.y}, WAKE_BODY);
}


void Box2D::setJointLength(u32 id, f32 length) {
	b2DistanceJoint_SetLength(m_joints.at(id), length * METERS_PER_PIXEL);
}

void Box2D::setJointSpring(u32 id, bool spring) {
	b2DistanceJoint_EnableSpring(m_joints.at(id), spring);
}


void Box2D::disableBody(u32 id) {
	b2Body_Disable(m_bodies.at(id));
}

void Box2D::enableBody(u32 id) {
	b2Body_Enable(m_bodies.at(id));
}


void Box2D::removeJoint(u32 id) {
	b2DestroyJoint(m_joints.at(id));
	m_joints.erase(id);
}

void Box2D::removeBody(u32 id) {
	if (!m_bodies.contains(id)) { return; }
	b2DestroyBody(m_bodies.at(id));
	m_bodies.erase(id);
	m_bodySizes.erase(id);
}


void Box2D::setBodyPosition(u32 id, const Math::Vec2 position) {
	b2Body_SetTransform(m_bodies[id], b2Vec2{position.x * METERS_PER_PIXEL, position.y * METERS_PER_PIXEL},
	                    b2Body_GetRotation(m_bodies[id]));
}

void Box2D::setBodyRotation(u32 id, f32 rotation) {
	b2Body_SetTransform(m_bodies[id], b2Body_GetPosition(m_bodies[id]), b2MakeRot(rotation));
}


Math::Vec2 Box2D::getJointAnchorA(u32 id) {
	b2Vec2 anchor = b2Joint_GetLocalAnchorA(m_joints.at(id));
	return Math::Vec2(anchor.x * PIXELS_PER_METER, anchor.y * PIXELS_PER_METER);
}

Math::Vec2 Box2D::getJointAnchorB(u32 id) {
	b2Vec2 anchor = b2Joint_GetLocalAnchorB(m_joints.at(id));
	return Math::Vec2(anchor.x * PIXELS_PER_METER, anchor.y * PIXELS_PER_METER);
}


Math::Vec2 Box2D::getBodyPosition(u32 id) {
	b2Vec2 position = b2Body_GetPosition(m_bodies[id]);
	return Math::Vec2(position.x * PIXELS_PER_METER - (m_bodySizes[id].x), position.y * PIXELS_PER_METER - (m_bodySizes[id].y));
}

f32 Box2D::getBodyRotation(u32 id) {
	return b2Rot_GetAngle(b2Body_GetRotation(m_bodies[id]));
}
