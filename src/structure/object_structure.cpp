#include <LTEngine/structure/object_structure.hpp>


using namespace LTEngine;
using namespace LTEngine::Object;


ObjectStructure::ObjectStructure() {
	_next_id = 0;
}


void ObjectStructure::Object::set_active(bool active) {
	_active = active;
}

void ObjectStructure::Object::set_visible(bool visible) {
	_visible = visible;
}


bool ObjectStructure::Object::is_active() const {
	return _active;
}

bool ObjectStructure::Object::is_visible() const {
	return _visible;
}


void ObjectStructure::Object::set_id(u32 id) {
	if (_id_set) { return; }
	_id = id;
	_id_set = true;
}

u32 ObjectStructure::Object::get_id() const {
	return _id;
}

void ObjectStructure::Object::set_object_structure(ObjectStructure *object_structure) {
	if (_structure == nullptr) { _structure = object_structure; }
}


void ObjectStructure::update(f32 delta) {
	for (u32 i = 0; i < _objects.size(); i++) { _objects[i]->update(delta); }
}

void ObjectStructure::render() {
	for (auto &object : _objects) {
		object->render();
	}
}


std::unique_ptr<EngineStructure::EngineStructureData> ObjectStructure::save() {
	return std::make_unique<ObjectStructureData>(ObjectStructureData{
		.objects = _objects
	});
}

void ObjectStructure::load(const EngineStructure::EngineStructureData *data) {
	_objects = ((ObjectStructureData*)data)->objects;
}


void ObjectStructure::clear() {
	_objects.clear();
}


u32 ObjectStructure::add_object(std::unique_ptr<Object> object) {
	u32 id = _next_id++;
	object->set_id(id);
	object->set_object_structure(this);
	_objects.push_back(std::move(object));
	return id;
}

u32 ObjectStructure::add_object(std::unique_ptr<Object> object, Math::Vec3 position) {
	object->set_position(position);
	return add_object(std::move(object));
}

u32 ObjectStructure::add_object(std::unique_ptr<Object> object, Math::Vec3 position, Math::Vec3 rotation) {
	object->set_position(position);
	object->set_rotation(rotation);
	return add_object(std::move(object));
}

u32 ObjectStructure::add_object(std::unique_ptr<Object> object, Math::Vec3 position, Math::Vec3 rotation, Math::Vec3 scale) {
	object->set_position(position);
	object->set_rotation(rotation);
	object->set_scale(scale);
	return add_object(std::move(object));
}

void ObjectStructure::remove_object(u32 id) {
	auto it = std::find_if(_objects.begin(), _objects.end(), [id](const std::shared_ptr<Object> &x) {
		if (x == nullptr) { return false; }
		return x->get_id() == id;
	});

	if (it != _objects.end()) { _objects.erase(it); }
}

ObjectStructure::Object *ObjectStructure::get_object(u32 id) {
	auto it = std::find_if(begin(), end(), [id](const Object *x) {
		if (x == nullptr) { return false; }
		return x->get_id() == id;
	});

	if (it != _objects.end()) { return *it; }

	return nullptr;
}


void ObjectStructure::add_tag(u32 id, const std::string &tag) {
	_object_tags[tag].push_back(id);
}

void ObjectStructure::remove_tag(u32 id, const std::string &tag) {
	if (!_object_tags.contains(tag)) { return; }
	_object_tags[tag].erase(std::remove(_object_tags[tag].begin(), _object_tags[tag].end(), id), _object_tags[tag].end());
}

bool ObjectStructure::has_tag(u32 id, const std::string &tag) {
	if (!_object_tags.contains(tag)) { return false; }
	return std::find(_object_tags[tag].begin(), _object_tags[tag].end(), id) != _object_tags[tag].end();
}
