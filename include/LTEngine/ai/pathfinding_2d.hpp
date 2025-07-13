#ifndef _LTENGINE_2D_PATHFINDING_HPP_
#define _LTENGINE_2D_PATHFINDING_HPP_

#include <vector>

#include <LTEngine/math/vec2.hpp>


namespace LTEngine::AI {
	class LTENGINE_API Pathfinding2D {
	public:
		virtual ~Pathfinding2D() = default;

		virtual void set_path(Math::Vec2i start, Math::Vec2i end) = 0;
		virtual bool is_possible_to_reach_in_theory() = 0;

		// If this is empty (it is by default), then the path will simply ignore the walkable path
		virtual void set_walkable_path(std::vector<Math::Vec2i> path) = 0;

		virtual u32 add_obstacle(Math::Vec2i pos) = 0;
		virtual void remove_obstacle(u32 id) = 0;

		// May throw NotPossibleException
		virtual std::vector<Math::Vec2i> calculate_path() = 0;
	};
} // namespace LTEngine::AI

#endif
