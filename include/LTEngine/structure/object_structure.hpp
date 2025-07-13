#ifndef _LTENGINE_OBJECT_STRUCTURE_HPP_
#define _LTENGINE_OBJECT_STRUCTURE_HPP_

#include <vector>
#include <unordered_map>

#include <LTEngine/structure/engine_structure.hpp>


namespace LTEngine::Object {
	class LTENGINE_API ObjectStructure : public EngineStructure {
	public:
		class Object;

		struct ObjectStructureData : EngineStructure::EngineStructureData {
			std::vector<std::shared_ptr<Object>> objects;
		};

		ObjectStructure();
		~ObjectStructure() override = default;

		class LTENGINE_API Object {
		public:
			struct ObjectData {
				Math::Vec3 position = Math::Vec3::Zero;
				Math::Vec3 rotation = Math::Vec3::Zero;
				Math::Vec3 scale = Math::Vec3::One;
			};
			virtual ~Object() = default;

			virtual void update(f32 delta) = 0;
			virtual void render() = 0;

			virtual std::unique_ptr<ObjectData> save() {
				return std::make_unique<ObjectData>(ObjectData{
					.position = getPosition(),
					.rotation = getRotation(),
					.scale = getScale(),
				});
			}
			virtual void load(const ObjectData *data) {
				setPosition(data->position);
				setScale(data->scale);
				setRotation(data->rotation);
			}

			virtual Math::Vec3 getPosition() const {
				return position;
			}
			virtual Math::Vec3 getScale() const {
				return scale;
			}
			virtual Math::Vec3 getRotation() const {
				return rotation;
			}
			virtual void setPosition(Math::Vec3 position) {
				this->position = position;
			}
			virtual void setScale(Math::Vec3 scale) {
				this->scale = scale;
			}
			virtual void setRotation(Math::Vec3 rotation) {
				this->rotation = rotation;
			}
			void translate(Math::Vec3 translation) {
				setPosition(position + translation);
			}

			bool isActive() const;
			bool isVisible() const;

			void setActive(bool active);
			void setVisible(bool visible);

			ObjectStructure *getObjectStructure() {
				return m_structure;
			}
			void setObjectStructure(ObjectStructure *structure);

			u32 getId() const;
			void setId(u32 id);

		protected:
			Math::Vec3 position = Math::Vec3::Zero;
			Math::Vec3 rotation = Math::Vec3::Zero;
			Math::Vec3 scale = Math::Vec3::One;

		private:
			bool m_active = true;
			bool m_visible = true;

			u32 m_id = 0;
			bool m_idSet = false;

			ObjectStructure *m_structure = nullptr;
		};

		struct ObjectIterator {
			using iterator_category = std::forward_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = Object *;
			using pointer = Object *;
			using reference = Object &;

			ObjectIterator(std::vector<std::shared_ptr<Object>>::iterator it) : m_it(it) {
			}

			Object *operator*() {
				return m_it->get();
			}
			Object *operator->() {
				return m_it->get();
			}

			ObjectIterator &operator++() {
				++m_it;
				return *this;
			}

			friend bool operator==(const ObjectIterator &a, const ObjectIterator &b) {
				return a.m_it == b.m_it;
			}
			friend bool operator!=(const ObjectIterator &a, const ObjectIterator &b) {
				return a.m_it != b.m_it;
			}

		private:
			std::vector<std::shared_ptr<Object>>::iterator m_it;
		};


		ObjectIterator begin() {
			return ObjectIterator(m_objects.begin());
		}
		ObjectIterator end() {
			return ObjectIterator(m_objects.end());
		}

		void update(f32 delta) override;
		void render() override;

		std::unique_ptr<EngineStructure::EngineStructureData> save() override;
		void load(const EngineStructure::EngineStructureData *data) override; 

		void clear() override;

		u32 addObject(std::unique_ptr<Object> object);
		u32 addObject(std::unique_ptr<Object> object, Math::Vec3 position);
		u32 addObject(std::unique_ptr<Object> object, Math::Vec3 position, Math::Vec3 scale);
		u32 addObject(std::unique_ptr<Object> object, Math::Vec3 position, Math::Vec3 rotation, Math::Vec3 scale);
		void removeObject(u32 id);
		Object *getObject(u32 id);

		void addTag(u32 id, const std::string &tag);
		void removeTag(u32 id, const std::string &tag);
		bool hasTag(u32 id, const std::string &tag);

	private:
		std::vector<std::shared_ptr<Object>> m_objects;
		std::unordered_map<std::string, std::vector<u32>> m_objectTags;

		u32 m_nextId;
	};
} // namespace LTEngine::Object

#endif
