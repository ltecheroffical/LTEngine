#ifndef _LTENGINE_ENGINE_STRUCTURE_HPP_
#define _LTENGINE_ENGINE_STRUCTURE_HPP_

#include <LTEngine/math/vec3.hpp>
#include <LTEngine/graphics/color.hpp>

namespace LTEngine::Object {
	class LTENGINE_API EngineStructure {
	public:
		struct EngineStructureData {};

		virtual ~EngineStructure() = default;

		virtual void update(f32 delta) = 0;
		virtual void render() = 0;

		virtual std::unique_ptr<EngineStructureData> save() = 0;
		virtual void load(const EngineStructureData *data) = 0;

		virtual void clear() = 0;
	};
} // namespace LTEngine::Object

#endif
