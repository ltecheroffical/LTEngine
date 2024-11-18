#ifndef _LTENGINE_OBJECT_STRUCTURE_HPP_
#define _LTENGINE_OBJECT_STRUCTURE_HPP_

#include <LTEngine/structure/engine_structure.hpp>


namespace LTEngine::Object {
	class ObjectStructure : public EngineStructure {
	public:
		ObjectStructure();
		~ObjectStructure() override = default;

		class Object {
		public:
			virtual ~Object() = default;

			virtual void update(f32 delta) = 0;
			virtual void render(LTEngine::Rendering::Renderer *renderer) = 0;

			virtual std::unique_ptr<Object> clone() const = 0;
			std::unique_ptr<Object> clone(u32 id) const;

			virtual Math::Vec2 getPosition() const { return position; }
			virtual Math::Vec2 getScale() const { return scale; }
			virtual f32 getRotation() const { return rotation; }
			virtual void setPosition(Math::Vec2 position) { this->position = position; }
			virtual void setScale(Math::Vec2 scale) { this->scale = scale; }
			virtual void setRotation(f32 rotation) { this->rotation = rotation; }
			void translate(Math::Vec2 translation) { setPosition(position + translation); }

			bool isActive() const;
			bool isVisible() const;

			void setActive(bool active);
			void setVisible(bool visible);

			ObjectStructure *getObjectStructure() { return m_structure; }
			void setObjectStructure(ObjectStructure *structure);

			u32 getId() const;
			void setId(u32 id);

		protected:
			Math::Vec2 position = Math::Vec2::Zero;
			Math::Vec2 scale = Math::Vec2::One;
			f32 rotation = 0.f;

		private:
			bool m_active = true;
			bool m_visible = true;

			u32 m_id = 0;
			bool m_idSet = false;

			ObjectStructure *m_structure = nullptr;
		};

		void update(f32 delta) override;
		void render(LTEngine::Rendering::Renderer *renderer) override;

		std::unique_ptr<EngineStructure> clone() const override;
		void clear() override;

		void setClearColor(Rendering::Color color);

		u32 addObject(std::unique_ptr<Object> object);
		u32 addObject(std::unique_ptr<Object> object, Math::Vec2 position);
		u32 addObject(std::unique_ptr<Object> object, Math::Vec2 position, f32 rotation);
		u32 addObject(std::unique_ptr<Object> object, Math::Vec2 position, Math::Vec2 scale);
		u32 addObject(std::unique_ptr<Object> object, Math::Vec2 position, f32 rotation, Math::Vec2 scale);
		void removeObject(u32 id);
		Object *getObject(u32 id);

	private:
		std::vector<std::unique_ptr<Object>> m_objects;

		u32 m_nextId;
	};
} // namespace LTEngine::Object

#endif
