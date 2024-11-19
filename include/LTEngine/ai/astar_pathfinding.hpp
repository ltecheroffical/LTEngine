#ifndef _LTENGINE_ASTAR_PATHFINDING_HPP_
#define _LTENGINE_ASTAR_PATHFINDING_HPP_

#include <functional>

#include <LTEngine/ai/pathfinding.hpp>


namespace LTEngine::AI {
	class AStarPathfinding : public Pathfinding {
	public:
		AStarPathfinding();
		~AStarPathfinding() override = default;

		void setPath(Math::Vec2i start, Math::Vec2i end) override;
		bool isPossibleToReach() override;

		void setWalkablePath(std::vector<Math::Vec2i> path) override;

		u32 addObstacle(Math::Vec2i pos) override;
		void removeObstacle(u32 id) override;

		std::vector<Math::Vec2i> getPath() override;

		void setCalculateHeristic(std::function<f32(Math::Vec2i, Math::Vec2i)> func) { m_heristicFunc = func; }
		void resetCalculateHeristic();

	private:
		struct Cell {
			i32 parent_i, parent_j;
			i32 f, g, h;
		};


		bool isValid(Math::Vec2i pos);
		bool isBlocked(Math::Vec2i pos);
		std::vector<Math::Vec2i> tracePath(std::vector<std::vector<Cell>> cellDetails);

		Math::Vec2i m_start = Math::Vec2i::Zero;
		Math::Vec2i m_end = Math::Vec2i::Zero;

		i32 m_offsetX = 0;
		i32 m_offsetY = 0;

		u32 m_gridWidth = 0;
		u32 m_gridHeight = 0;

		u32 m_nextObstacleId = 0;

		std::vector<Math::Vec2i> m_walkableTiles;
		std::unordered_map<u32, Math::Vec2i> m_obstacles;

		std::function<f32(Math::Vec2i, Math::Vec2i)> m_heristicFunc;
	};
} // namespace LTEngine::AI

#endif
