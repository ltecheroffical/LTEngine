#include <acutest.h>

#include <LTEngine/ai/astar_pathfinding.hpp>


void test_astar_pathfinding() {
	LTEngine::AI::AStarPathfinding pathfinding;

	LTEngine::Math::Vec2i position = LTEngine::Math::Vec2i::Zero;
	const LTEngine::Math::Vec2i target = LTEngine::Math::Vec2i(-50, -120);

	pathfinding.setPath(position, target);

	pathfinding.addObstacle(LTEngine::Math::Vec2i::Left);
	pathfinding.addObstacle(LTEngine::Math::Vec2i::Right);

	std::vector<LTEngine::Math::Vec2i> path = pathfinding.calculatePath();
	for (LTEngine::Math::Vec2i direction : path) { position += direction; }

	TEST_CHECK(position == target);
	TEST_MSG("Expected: (%d, %d), Got: (%d, %d)", target.x, target.y, position.x, position.y);
}

TEST_LIST = {{"test_astar_pathfinding", test_astar_pathfinding},

             {NULL, NULL}};
