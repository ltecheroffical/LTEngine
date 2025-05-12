#ifndef _LTCORE_ENGINE_STRUCTURE_HPP_
#define _LTCORE_ENGINE_STRUCTURE_HPP_

#include <LTCore/math/vec3.hpp>
#include <LTCore/graphics/color.hpp>

namespace LTCore::Object {
	class LTCORE_API EngineStructure {
	public:
		struct EngineStructureData {};

		virtual ~EngineStructure() = default;

		virtual void update(f32 delta) = 0;
		virtual void render() = 0;

		virtual std::unique_ptr<EngineStructureData> save() = 0;
		virtual void load(const EngineStructureData *data) = 0;

		virtual void clear() = 0;
	};
} // namespace LTCore::Object

#endif
