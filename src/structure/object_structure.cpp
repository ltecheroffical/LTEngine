#include <LTEngine/structure/object_structure.hpp>


using namespace LTEngine;
using namespace LTEngine::Object;


ObjectStructure::ObjectStructure() {
	m_nextId = 0;
}


std::unique_ptr<ObjectStructure::Object> ObjectStructure::Object::clone(u32 id) const {
	std::unique_ptr<ObjectStructure::Object> obj = clone();
	obj->setId(id);
	return obj;
}


void ObjectStructure::Object::setActive(bool active) {
	m_active = active;
}

void ObjectStructure::Object::setVisible(bool visible) {
	m_visible = visible;
}


bool ObjectStructure::Object::isActive() const {
	return m_active;
}

bool ObjectStructure::Object::isVisible() const {
	return m_visible;
}


void ObjectStructure::Object::setId(u32 id) {
	if (m_idSet) { return; }
	m_id = id;
	m_idSet = true;
}

u32 ObjectStructure::Object::getId() const {
	return m_id;
}

void ObjectStructure::Object::setObjectStructure(ObjectStructure *objectStructure) {
	if (m_structure == nullptr) { m_structure = objectStructure; }
}


void ObjectStructure::update(f32 delta) {
	for (u32 i = 0; i < m_objects.size(); i++) { m_objects[i]->update(delta); }
}

void ObjectStructure::render(LTEngine::Rendering::Renderer *renderer) {
	for (auto &object : m_objects) {
		renderer->resetTransform();
		renderer->setPositionOffset(object->getPosition());
		renderer->setRotationOffset(object->getRotation());
		renderer->setScaleFactor(object->getScale());
		renderer->setZOrder(0);
		renderer->clearIrisMode();
		renderer->setOffsetsApplied();

		object->render(renderer);
	}
}


std::unique_ptr<EngineStructure> ObjectStructure::clone() const {
	auto object_structure = std::make_unique<ObjectStructure>();

	for (auto &object : m_objects) { object_structure->m_objects.push_back(object->clone()); }

	object_structure->m_clearColor = m_clearColor;
	object_structure->m_nextId = m_nextId;

	return object_structure;
}

void ObjectStructure::clear() {
	m_objects.clear();
}


void ObjectStructure::setClearColor(Rendering::Color color) {
	m_clearColor = color;
}


u32 ObjectStructure::addObject(std::unique_ptr<Object> object) {
	u32 id = m_nextId++;
	object->setId(id);
	object->setObjectStructure(this);
	m_objects.push_back(std::move(object));
	return id;
}

u32 ObjectStructure::addObject(std::unique_ptr<Object> object, Math::Vec2 position) {
	object->setPosition(position);
	return addObject(std::move(object));
}

u32 ObjectStructure::addObject(std::unique_ptr<Object> object, Math::Vec2 position, f32 rotation) {
	object->setPosition(position);
	object->setRotation(rotation);
	return addObject(std::move(object));
}

u32 ObjectStructure::addObject(std::unique_ptr<Object> object, Math::Vec2 position, Math::Vec2 scale) {
	object->setPosition(position);
	object->setScale(scale);
	return addObject(std::move(object));
}

u32 ObjectStructure::addObject(std::unique_ptr<Object> object, Math::Vec2 position, f32 rotation, Math::Vec2 scale) {
	object->setPosition(position);
	object->setRotation(rotation);
	object->setScale(scale);
	return addObject(std::move(object));
}

void ObjectStructure::removeObject(u32 id) {
	auto it = std::find_if(m_objects.begin(), m_objects.end(), [id](const std::shared_ptr<Object> &x) {
		if (x == nullptr) { return false; }
		return x->getId() == id;
	});

	if (it != m_objects.end()) { m_objects.erase(it); }
}

ObjectStructure::Object *ObjectStructure::getObject(u32 id) {
	auto it = std::find_if(begin(), end(), [id](const Object *x) {
		if (x == nullptr) { return false; }
		return x->getId() == id;
	});

	if (it != m_objects.end()) { return *it; }

	return nullptr;
}


void ObjectStructure::addTag(u32 id, const std::string &tag) {
	m_objectTags[tag].push_back(id);
}

void ObjectStructure::removeTag(u32 id, const std::string &tag) {
	if (!m_objectTags.contains(tag)) { return; }
	m_objectTags[tag].erase(std::remove(m_objectTags[tag].begin(), m_objectTags[tag].end(), id), m_objectTags[tag].end());
}

bool ObjectStructure::hasTag(u32 id, const std::string &tag) {
	if (!m_objectTags.contains(tag)) { return false; }
	return std::find(m_objectTags[tag].begin(), m_objectTags[tag].end(), id) != m_objectTags[tag].end();
}
