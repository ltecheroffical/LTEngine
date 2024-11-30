#ifndef _LTENGINE_PATHFINDING_HPP_
#define _LTENGINE_PATHFINDING_HPP_

#include <vector>

#include <LTEngine/common/types/inttypes.h>

#include <LTEngine/math/vec2.hpp>


namespace LTEngine::AI {
	class Pathfinding {
	public:
		virtual ~Pathfinding() = default;

		virtual void setPath(Math::Vec2i start, Math::Vec2i end) = 0;
		virtual bool isPossibleToReach() = 0;

		virtual void setWalkablePath(std::vector<Math::Vec2i> path) = 0;

		virtual u32 addObstacle(Math::Vec2i pos) = 0;
		virtual void removeObstacle(u32 id) = 0;

		/**
		 * @brief Returns the directions to the target
		 *
		 * @details
		 * This recalculates the path every time it is called.
		 * If you do not want this to happen. The result should be cached at the
		 * application level.
		 */
		virtual std::vector<Math::Vec2i> getPath() = 0;
	};
} // namespace LTEngine::AI

#endif
