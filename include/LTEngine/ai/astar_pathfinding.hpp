#ifndef _LTENGINE_ASTAR_PATHFINDING_HPP_
#define _LTENGINE_ASTAR_PATHFINDING_HPP_

#include <functional>

#include <LTEngine/ai/pathfinding_2d.hpp>


namespace LTEngine::AI {
	class LTENGINE_API AStarPathfinding : public Pathfinding2D {
	public:
		AStarPathfinding();
		~AStarPathfinding() override = default;

		void set_path(Math::Vec2i start, Math::Vec2i end) override;
		bool is_possible_to_reach_in_theory() override;

		void set_walkable_path(std::vector<Math::Vec2i> path) override;

		u32 add_obstacle(Math::Vec2i pos) override;
		void remove_obstacle(u32 id) override;

		std::vector<Math::Vec2i> calculate_path() override;

		void set_calculate_heristic(std::function<f32(Math::Vec2i a, Math::Vec2i b)> func) {
			_heristic_func = func;
		}
		void reset_calculate_heristic();

	private:
		struct Cell {
			i32 parent_i, parent_j;
			i32 f, g, h;
		};


		bool _is_valid(Math::Vec2i pos);
		bool _is_blocked(Math::Vec2i pos);
		std::vector<Math::Vec2i> _trace_path(std::vector<std::vector<Cell>> cell_details);

		Math::Vec2i _start = Math::Vec2i::ZERO;
		Math::Vec2i _end = Math::Vec2i::ZERO;

		i32 _offset_x = 0;
		i32 _offset_y = 0;

		u32 _grid_width = 0;
		u32 _grid_height = 0;

		u32 _next_obstacle_id = 0;

		std::vector<Math::Vec2i> _walkable_tiles;
		std::unordered_map<u32, Math::Vec2i> _obstacles;

		std::function<f32(Math::Vec2i, Math::Vec2i)> _heristic_func;
	};
} // namespace LTEngine::AI

#endif
