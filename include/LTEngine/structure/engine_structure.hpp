#ifndef _LTENGINE_ENGINE_STRUCTURE_HPP_
#define _LTENGINE_ENGINE_STRUCTURE_HPP_

#include <LTEngine/rendering/renderer.hpp>


namespace LTEngine::Object {
	class LTENGINE_API EngineStructure {
	public:
		virtual ~EngineStructure() = default;

		virtual void update(f32 delta) = 0;
		virtual void render(LTEngine::Rendering::Renderer *renderer) = 0;

		virtual std::unique_ptr<EngineStructure> clone() const = 0;

		virtual void clear() = 0;

		Rendering::Color getClearColor() const;

	protected:
		Rendering::Color m_clearColor;
	};
} // namespace LTEngine::Object

#endif
