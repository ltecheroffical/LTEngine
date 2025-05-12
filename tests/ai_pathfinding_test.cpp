#include <catch2/catch_test_macros.hpp>

#include <LTCore/ai/astar_pathfinding.hpp>


TEST_CASE("The A* pathfinding should correctly find a path", "[astar]") {
	LTCore::AI::AStarPathfinding pathfinding;

	LTCore::Math::Vec2i position = LTCore::Math::Vec2i::Zero;
	const LTCore::Math::Vec2i target = LTCore::Math::Vec2i(-50, -120);

	pathfinding.setPath(position, target);

	pathfinding.addObstacle(LTCore::Math::Vec2i::Left);
	pathfinding.addObstacle(LTCore::Math::Vec2i::Right);

	std::vector<LTCore::Math::Vec2i> path = pathfinding.calculatePath();
	for (LTCore::Math::Vec2i direction : path) {
		position += direction;
	}

	REQUIRE(position == target);
}
