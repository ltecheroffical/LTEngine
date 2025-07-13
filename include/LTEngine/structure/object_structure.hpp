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
				Math::Vec3 position = Math::Vec3::ZERO;
				Math::Vec3 rotation = Math::Vec3::ZERO;
				Math::Vec3 scale = Math::Vec3::ONE;
			};
			virtual ~Object() = default;

			virtual void update(f32 delta) = 0;
			virtual void render() = 0;

			virtual std::unique_ptr<ObjectData> save() {
				return std::make_unique<ObjectData>(ObjectData{
					.position = get_position(),
					.rotation = get_rotation(),
					.scale = get_scale(),
				});
			}
			virtual void load(const ObjectData *data) {
				set_position(data->position);
				set_scale(data->scale);
				set_rotation(data->rotation);
			}

			virtual Math::Vec3 get_position() const {
				return position;
			}
			virtual Math::Vec3 get_scale() const {
				return scale;
			}
			virtual Math::Vec3 get_rotation() const {
				return rotation;
			}
			virtual void set_position(Math::Vec3 position) {
				this->position = position;
			}
			virtual void set_scale(Math::Vec3 scale) {
				this->scale = scale;
			}
			virtual void set_rotation(Math::Vec3 rotation) {
				this->rotation = rotation;
			}
			void translate(Math::Vec3 translation) {
				set_position(position + translation);
			}

			bool is_active() const;
			bool is_visible() const;

			void set_active(bool active);
			void set_visible(bool visible);

			ObjectStructure *get_object_structure() {
				return _structure;
			}
			void set_object_structure(ObjectStructure *structure);

			u32 get_id() const;
			void set_id(u32 id);

		protected:
			Math::Vec3 position = Math::Vec3::ZERO;
			Math::Vec3 rotation = Math::Vec3::ZERO;
			Math::Vec3 scale = Math::Vec3::ONE;

		private:
			bool _active = true;
			bool _visible = true;

			u32 _id = 0;
			bool _id_set = false;

			ObjectStructure *_structure = nullptr;
		};

		struct ObjectIterator {
			using iterator_category = std::forward_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = Object *;
			using pointer = Object *;
			using reference = Object &;

			ObjectIterator(std::vector<std::shared_ptr<Object>>::iterator it) : _it(it) {
			}

			Object *operator*() {
				return _it->get();
			}
			Object *operator->() {
				return _it->get();
			}

			ObjectIterator &operator++() {
				++_it;
				return *this;
			}

			friend bool operator==(const ObjectIterator &a, const ObjectIterator &b) {
				return a._it == b._it;
			}
			friend bool operator!=(const ObjectIterator &a, const ObjectIterator &b) {
				return a._it != b._it;
			}

		private:
			std::vector<std::shared_ptr<Object>>::iterator _it;
		};


		ObjectIterator begin() {
			return ObjectIterator(_objects.begin());
		}
		ObjectIterator end() {
			return ObjectIterator(_objects.end());
		}

		void update(f32 delta) override;
		void render() override;

		std::unique_ptr<EngineStructure::EngineStructureData> save() override;
		void load(const EngineStructure::EngineStructureData *data) override; 

		void clear() override;

		u32 add_object(std::unique_ptr<Object> object);
		u32 add_object(std::unique_ptr<Object> object, Math::Vec3 position);
		u32 add_object(std::unique_ptr<Object> object, Math::Vec3 position, Math::Vec3 scale);
		u32 add_object(std::unique_ptr<Object> object, Math::Vec3 position, Math::Vec3 rotation, Math::Vec3 scale);
		void remove_object(u32 id);
		Object *get_object(u32 id);

		void add_tag(u32 id, const std::string &tag);
		void remove_tag(u32 id, const std::string &tag);
		bool has_tag(u32 id, const std::string &tag);

	private:
		std::vector<std::shared_ptr<Object>> _objects;
		std::unordered_map<std::string, std::vector<u32>> _object_tags;

		u32 _next_id;
	};
} // namespace LTEngine::Object

#endif
