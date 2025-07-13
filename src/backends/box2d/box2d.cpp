#ifdef LTENGINE_COMPONENT_PHYSICS_BOX2D
#include <LTEngine/backends/box2d/box2d.hpp>

using namespace LTEngine;
using namespace LTEngine::Physics;

const f32 PIXELS_PER_METER = 50.f;
const f32 METERS_PER_PIXEL = 1.f / PIXELS_PER_METER;

Box2D::Box2D() {
	b2WorldDef world_def = b2DefaultWorldDef();

	world_def.gravity = b2Vec2{0.f, 0.f};

	b2WorldId world_id = b2CreateWorld(&world_def);
	_world = world_id;
}

Box2D::~Box2D() {
	_bodies.clear();
	_joints.clear();

	_body_sizes.clear();
	b2DestroyWorld(_world);
}

void Box2D::update(f32 time_step) {
	b2World_Step(_world, time_step, 4);
	std::for_each(_bodies.begin(), _bodies.end(), [this](std::pair<u32, b2BodyId> pair) {
		b2ContactData contact_data[b2Body_GetContactCapacity(pair.second)];
		u32 contact_count = b2Body_GetContactData(pair.second, contact_data, b2Body_GetContactCapacity(pair.second));

		for (u32 i = 0; i < contact_count; i++) {
			b2BodyId body_b = b2Shape_GetBody(contact_data[i].shapeIdB);

			auto other_body = std::find_if(_bodies.begin(), _bodies.end(), [body_b](std::pair<u32, b2BodyId> body_pair) {
				// We have to compare everything since Box2D doesn't provide an id comparison function
				return body_b.generation == body_pair.second.generation && body_b.index1 == body_pair.second.index1 &&
				       body_b.world0 == body_pair.second.world0;
			});

			on_body_collision(pair.first, other_body->first);
		}
	});
}

void Box2D::set_gravity(const Math::Vec2 &gravity) {
	b2World_SetGravity(_world, b2Vec2{gravity.x, gravity.y});
}

Math::Vec2 Box2D::get_gravity() const {
	return Math::Vec2(b2World_GetGravity(_world).x, b2World_GetGravity(_world).y);
}

u32 Box2D::add_body(Shapes::Rect rect, PhysicsEngine2D::BodyType body_type) {
	b2BodyDef body_def = b2DefaultBodyDef();

	switch (body_type) {
		default:
		case PhysicsEngine2D::BodyType::BODY_TYPE_STATIC:
			body_def.type = b2_staticBody;
			break;
		case PhysicsEngine2D::BodyType::BODY_TYPE_DYNAMIC:
			body_def.type = b2_dynamicBody;
			break;
		case PhysicsEngine2D::BodyType::BODY_TYPE_KINEMATIC:
			body_def.type = b2_kinematicBody;
			break;
	}

	body_def.position = b2Vec2{(rect.x + rect.w) * METERS_PER_PIXEL, (rect.y + rect.h) * METERS_PER_PIXEL};
	body_def.rotation = b2MakeRot(rect.rotation);

	b2BodyId body_id = b2CreateBody(_world, &body_def);
	b2Polygon shape = b2MakeBox(rect.w * METERS_PER_PIXEL, rect.h * METERS_PER_PIXEL);

	b2ShapeDef shape_def = b2DefaultShapeDef();
	b2CreatePolygonShape(body_id, &shape_def, &shape);

	u32 id = _next_id++;
	_bodies[id] = body_id;
	_body_sizes[id] = b2Vec2{(f32)rect.w, (f32)rect.h};
	return id;
}

u32 Box2D::add_body(Shapes::Circle circle, PhysicsEngine2D::BodyType body_type) {
	b2BodyDef body_def = b2DefaultBodyDef();

	switch (body_type) {
		default:
		case PhysicsEngine2D::BodyType::BODY_TYPE_STATIC:
			body_def.type = b2_staticBody;
			break;
		case PhysicsEngine2D::BodyType::BODY_TYPE_DYNAMIC:
			body_def.type = b2_dynamicBody;
			break;
		case PhysicsEngine2D::BodyType::BODY_TYPE_KINEMATIC:
			body_def.type = b2_kinematicBody;
			break;
	}

	body_def.position = b2Vec2{circle.x * METERS_PER_PIXEL, circle.y * METERS_PER_PIXEL};
	body_def.rotation = b2MakeRot(circle.rotation);

	b2BodyId body_id = b2CreateBody(_world, &body_def);

	b2Circle shape;
	shape.radius = circle.radius * METERS_PER_PIXEL;
	shape.center = b2Vec2{circle.x * METERS_PER_PIXEL, circle.y * METERS_PER_PIXEL};

	b2ShapeDef shape_def = b2DefaultShapeDef();
	b2CreateCircleShape(body_id, &shape_def, &shape);

	u32 id = _next_id++;
	_bodies[id] = body_id;
	return id;
}

u32 Box2D::add_body(Shapes::Polygon polygon, PhysicsEngine2D::BodyType body_type) {
	b2BodyDef body_def = b2DefaultBodyDef();

	switch (body_type) {
		default:
		case PhysicsEngine2D::BodyType::BODY_TYPE_STATIC:
			body_def.type = b2_staticBody;
			break;
		case PhysicsEngine2D::BodyType::BODY_TYPE_DYNAMIC:
			body_def.type = b2_dynamicBody;
			break;
		case PhysicsEngine2D::BodyType::BODY_TYPE_KINEMATIC:
			body_def.type = b2_kinematicBody;
			break;
	}

	body_def.position = b2Vec2{polygon.x * METERS_PER_PIXEL, polygon.y * METERS_PER_PIXEL};
	body_def.rotation = b2MakeRot(polygon.rotation);

	b2BodyId body_id = b2CreateBody(_world, &body_def);

	std::vector<b2Vec2> points;
	for (Math::Vec2 point : polygon.points) {
		points.push_back(b2Vec2{point.x * METERS_PER_PIXEL, point.y * METERS_PER_PIXEL});
	}
	b2Hull hull = b2ComputeHull(points.data(), points.size());

	const f32 radius = 0.1f; // Box2D, why is this a requirement?
	b2Polygon shape = b2MakePolygon(&hull, radius);

	b2ShapeDef shape_def = b2DefaultShapeDef();
	b2CreatePolygonShape(body_id, &shape_def, &shape);

	u32 id = _next_id++;
	_bodies[id] = body_id;
	return id;
}

u32 Box2D::add_body(Shapes::Triangle triangle, PhysicsEngine2D::BodyType body_type) {
	b2BodyDef body_def = b2DefaultBodyDef();

	switch (body_type) {
		default:
		case PhysicsEngine2D::BodyType::BODY_TYPE_STATIC:
			body_def.type = b2_staticBody;
			break;
		case PhysicsEngine2D::BodyType::BODY_TYPE_DYNAMIC:
			body_def.type = b2_dynamicBody;
			break;
		case PhysicsEngine2D::BodyType::BODY_TYPE_KINEMATIC:
			body_def.type = b2_kinematicBody;
			break;
	}

	body_def.position = b2Vec2{triangle.x * METERS_PER_PIXEL, triangle.y * METERS_PER_PIXEL};
	body_def.rotation = b2MakeRot(triangle.rotation);

	b2BodyId body_id = b2CreateBody(_world, &body_def);

	b2Vec2 points[3] = {b2Vec2{triangle.p1.x * METERS_PER_PIXEL, triangle.p1.y * METERS_PER_PIXEL},
	                    b2Vec2{triangle.p2.x * METERS_PER_PIXEL, triangle.p2.y * METERS_PER_PIXEL},
	                    b2Vec2{triangle.p3.x * METERS_PER_PIXEL, triangle.p3.y * METERS_PER_PIXEL}};
	b2Hull hull = b2ComputeHull(points, 3);

	const f32 radius = 0.1f; // Box2D, why is this a requirement?
	b2Polygon shape = b2MakePolygon(&hull, radius);

	b2ShapeDef shape_def = b2DefaultShapeDef();
	b2CreatePolygonShape(body_id, &shape_def, &shape);

	u32 id = _next_id++;
	_bodies[id] = body_id;
	return id;
}

u32 Box2D::add_joint(u32 body_id_a, u32 body_id_b, const Math::Vec2 anchor_a, const Math::Vec2 anchor_b) {
	b2DistanceJointDef joint_def; // What is that type name?
	joint_def.bodyIdA = _bodies.at(body_id_a);
	joint_def.bodyIdB = _bodies.at(body_id_b);
	joint_def.localAnchorA = b2Vec2{anchor_a.x * METERS_PER_PIXEL, anchor_a.y * METERS_PER_PIXEL};
	joint_def.localAnchorB = b2Vec2{anchor_b.x * METERS_PER_PIXEL, anchor_b.y * METERS_PER_PIXEL};

	b2JointId joint_id = b2CreateDistanceJoint(_world, &joint_def);
	u32 id = _next_id++;
	_joints[id] = joint_id;
	return id;
}

void Box2D::add_force(u32 id, Math::Vec2 force) {
	const bool wake_body = true;
	b2Body_ApplyForceToCenter(_bodies.at(id), b2Vec2{force.x, force.y}, wake_body);
}

void Box2D::set_joint_length(u32 id, f32 length) {
	b2DistanceJoint_SetLength(_joints.at(id), length * METERS_PER_PIXEL);
}

void Box2D::set_joint_spring(u32 id, bool spring) {
	b2DistanceJoint_EnableSpring(_joints.at(id), spring);
}

void Box2D::disable_body(u32 id) {
	b2Body_Disable(_bodies.at(id));
}

void Box2D::enable_body(u32 id) {
	b2Body_Enable(_bodies.at(id));
}

void Box2D::remove_joint(u32 id) {
	b2DestroyJoint(_joints.at(id));
	_joints.erase(id);
}

void Box2D::remove_body(u32 id) {
	if (!_bodies.contains(id)) {
		return;
	}
	b2DestroyBody(_bodies.at(id));
	_bodies.erase(id);
	_body_sizes.erase(id);
}

void Box2D::set_body_position(u32 id, const Math::Vec2 position) {
	b2Body_SetTransform(_bodies[id], b2Vec2{position.x * METERS_PER_PIXEL, position.y * METERS_PER_PIXEL},
	                    b2Body_GetRotation(_bodies[id]));
}

void Box2D::set_body_rotation(u32 id, f32 rotation) {
	b2Body_SetTransform(_bodies[id], b2Body_GetPosition(_bodies[id]), b2MakeRot(rotation));
}

Math::Vec2 Box2D::get_joint_anchor_a(u32 id) {
	b2Vec2 anchor = b2Joint_GetLocalAnchorA(_joints.at(id));
	return Math::Vec2(anchor.x * PIXELS_PER_METER, anchor.y * PIXELS_PER_METER);
}

Math::Vec2 Box2D::get_joint_anchor_b(u32 id) {
	b2Vec2 anchor = b2Joint_GetLocalAnchorB(_joints.at(id));
	return Math::Vec2(anchor.x * PIXELS_PER_METER, anchor.y * PIXELS_PER_METER);
}

Math::Vec2 Box2D::get_body_position(u32 id) {
	b2Vec2 position = b2Body_GetPosition(_bodies[id]);
	return Math::Vec2(position.x * PIXELS_PER_METER - (_body_sizes[id].x), position.y * PIXELS_PER_METER - (_body_sizes[id].y));
}

f32 Box2D::get_body_rotation(u32 id) {
	return b2Rot_GetAngle(b2Body_GetRotation(_bodies[id]));
}

#endif