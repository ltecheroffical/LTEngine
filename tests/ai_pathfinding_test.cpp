#include <catch2/catch_test_macros.hpp>

#include <LTEngine/ai/astar_pathfinding.hpp>


TEST_CASE("The A* pathfinding should correctly find a path", "[astar]") {
	LTEngine::AI::AStarPathfinding pathfinding;

	LTEngine::Math::Vec2i position = LTEngine::Math::Vec2i::Zero;
	const LTEngine::Math::Vec2i target = LTEngine::Math::Vec2i(-50, -120);

	pathfinding.setPath(position, target);

	pathfinding.addObstacle(LTEngine::Math::Vec2i::Left);
	pathfinding.addObstacle(LTEngine::Math::Vec2i::Right);

	std::vector<LTEngine::Math::Vec2i> path = pathfinding.calculatePath();
	for (LTEngine::Math::Vec2i direction : path) {
		position += direction;
	}

	REQUIRE(position == target);
}
