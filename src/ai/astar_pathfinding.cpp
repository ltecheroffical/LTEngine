#include <set>

#include <LTEngine/ai/astar_pathfinding.hpp>


using namespace LTEngine;
using namespace LTEngine::AI;


AStarPathfinding::AStarPathfinding() {
	resetCalculateHeristic();
}


void AStarPathfinding::setPath(Math::Vec2i start, Math::Vec2i end) {
	m_start = start;
	m_end = end;

	// Initialize grid dimensions and offsets
	m_offsetX = 0;
	m_offsetY = 0;

	// Determine minimum and maximum coordinates
	int minX = std::min(m_start.x, m_end.x);
	int minY = std::min(m_start.y, m_end.y);
	int maxX = std::max(m_start.x, m_end.x);
	int maxY = std::max(m_start.y, m_end.y);

	// Check for negative coordinates and adjust grid size
	if (minX < 0) {
		m_offsetX = -minX;               // Offset for negative X
		m_gridWidth = (maxX - minX) * 2; // Double grid size on X-axis
	} else {
		m_gridWidth = maxX - minX + 1; // Normal size
	}

	if (minY < 0) {
		m_offsetY = -minY;                // Offset for negative Y
		m_gridHeight = (maxY - minY) * 2; // Double grid size on Y-axis
	} else {
		m_gridHeight = maxY - minY + 1; // Normal size
	}
}

bool AStarPathfinding::isPossibleToReach() {
	if (!isValid(m_start) || !isValid(m_end)) { return false; }
	if (isBlocked(m_end)) { return false; }
	return true;
}


void AStarPathfinding::setWalkablePath(std::vector<Math::Vec2i> path) {
	m_walkableTiles = path;
}


u32 AStarPathfinding::addObstacle(Math::Vec2i pos) {
	u32 id = m_nextObstacleId++;
	m_obstacles[id] = pos;
	return id;
}

void AStarPathfinding::removeObstacle(u32 id) {
	m_obstacles.erase(id);
}


std::vector<Math::Vec2i> AStarPathfinding::calculatePath() {
	if (!isValid(m_start) || !isValid(m_end)) { return {}; }
	if (isBlocked(m_end)) { return {}; }

	std::vector<std::vector<bool>> closedList(m_gridHeight, std::vector<bool>(m_gridWidth, false));
	std::vector<std::vector<Cell>> cellDetails(m_gridHeight, std::vector<Cell>(m_gridWidth));

	for (u32 i = 0; i < m_gridWidth; ++i) {
		for (u32 j = 0; j < m_gridHeight; ++j) {
			cellDetails[j][i].f = std::numeric_limits<i32>().max();
			cellDetails[j][i].g = std::numeric_limits<i32>().max();
			cellDetails[j][i].h = std::numeric_limits<i32>().max();
			cellDetails[j][i].parent_i = i;
			cellDetails[j][i].parent_j = j;
		}
	}

	u32 i = m_start.x + m_offsetX, j = m_start.y + m_offsetY;
	cellDetails[j][i].f = 0;
	cellDetails[j][i].g = 0;
	cellDetails[j][i].h = 0;
	cellDetails[j][i].parent_i = i;
	cellDetails[j][i].parent_j = j;


	std::set<std::pair<f32, Math::Vec2i>> openList;

	openList.insert(std::make_pair(0.0, Math::Vec2i(m_start.x, m_start.y)));

	while (!openList.empty()) {
		std::pair<f32, Math::Vec2i> p = *openList.begin();
		openList.erase(openList.begin());

		i = p.second.x + m_offsetX;
		j = p.second.y + m_offsetY;
		closedList[j][i] = true;

		f64 gNew, hNew, fNew;

		// Successor 1 (Right)
		if (isValid(Math::Vec2i(i - 1 - m_offsetX, j - m_offsetY))) {
			if ((i - 1 - m_offsetX) == m_end.x && j - m_offsetY == m_end.y) {
				cellDetails[j][i - 1].parent_i = i;
				cellDetails[j][i - 1].parent_j = j;
				return tracePath(cellDetails);
			} else if (!closedList[j][i - 1] && !isBlocked(Math::Vec2i(i - 1 - m_offsetX, j - m_offsetY))) {
				gNew = cellDetails[j][i].g + 1.f;
				hNew = m_heristicFunc(Math::Vec2i(i - 1, j), m_end);
				fNew = gNew + hNew;

				if (cellDetails[j][i - 1].f == std::numeric_limits<i32>().max() || cellDetails[j][i - 1].f > fNew) {
					openList.insert(std::make_pair(fNew, Math::Vec2i(i - 1 - m_offsetX, j - m_offsetY)));
					cellDetails[j][i - 1].f = fNew;
					cellDetails[j][i - 1].g = gNew;
					cellDetails[j][i - 1].h = hNew;
					cellDetails[j][i - 1].parent_i = i;
					cellDetails[j][i - 1].parent_j = j;
				}
			}
		}

		// Successor 2 (Left)
		if (isValid(Math::Vec2i(i + 1 - m_offsetX, j - m_offsetY))) {
			if ((i + 1 - m_offsetX) == m_end.x && j - m_offsetY == m_end.y) {
				cellDetails[j][i + 1].parent_i = i;
				cellDetails[j][i + 1].parent_j = j;
				return tracePath(cellDetails);
			} else if (!closedList[j][i + 1] && !isBlocked(Math::Vec2i(i + 1 - m_offsetX, j - m_offsetY))) {
				gNew = cellDetails[j][i].g + 1.f;
				hNew = m_heristicFunc(Math::Vec2i(i + 1, j), m_end);
				fNew = gNew + hNew;

				if (cellDetails[j][i + 1].f == std::numeric_limits<i32>().max() || cellDetails[j][i + 1].f > fNew) {
					openList.insert(std::make_pair(fNew, Math::Vec2i(i + 1 - m_offsetX, j - m_offsetY)));
					cellDetails[j][i + 1].f = fNew;
					cellDetails[j][i + 1].g = gNew;
					cellDetails[j][i + 1].h = hNew;
					cellDetails[j][i + 1].parent_i = i;
					cellDetails[j][i + 1].parent_j = j;
				}
			}
		}

		// Successor 3 (Down)
		if (isValid(Math::Vec2i(i - m_offsetX, j + 1 - m_offsetY))) {
			if (i - m_offsetX == m_end.x && (j + 1 - m_offsetY) == m_end.y) {
				cellDetails[j + 1][i].parent_i = i;
				cellDetails[j + 1][i].parent_j = j;
				return tracePath(cellDetails);
			} else if (!closedList[j + 1][i] && !isBlocked(Math::Vec2i(i - m_offsetX, j + 1 - m_offsetY))) {
				gNew = cellDetails[j][i].g + 1.f;
				hNew = m_heristicFunc(Math::Vec2i(i, j + 1), m_end);
				fNew = gNew + hNew;

				if (cellDetails[j + 1][i].f == std::numeric_limits<i32>().max() || cellDetails[j + 1][i].f > fNew) {
					openList.insert(std::make_pair(fNew, Math::Vec2i(i - m_offsetX, j + 1 - m_offsetY)));
					cellDetails[j + 1][i].f = fNew;
					cellDetails[j + 1][i].g = gNew;
					cellDetails[j + 1][i].h = hNew;
					cellDetails[j + 1][i].parent_i = i;
					cellDetails[j + 1][i].parent_j = j;
				}
			}
		}

		// Successor 4 (Up)
		if (isValid(Math::Vec2i(i - m_offsetX, j - 1 - m_offsetY))) {
			if (i - m_offsetX == m_end.x && (j - 1 - m_offsetY) == m_end.y) {
				cellDetails[j - 1][i].parent_i = i;
				cellDetails[j - 1][i].parent_j = j;
				return tracePath(cellDetails);
			} else if (!closedList[j - 1][i] && !isBlocked(Math::Vec2i(i - m_offsetX, j - 1 - m_offsetY))) {
				gNew = cellDetails[j][i].g + 1.f;
				hNew = m_heristicFunc(Math::Vec2i(i - m_offsetX, j - 1 - m_offsetY), m_end);
				fNew = gNew + hNew;

				if (cellDetails[j - 1][i].f == std::numeric_limits<i32>().max() || cellDetails[j - 1][i].f > fNew) {
					openList.insert(std::make_pair(fNew, Math::Vec2i(i - m_offsetX, j - 1 - m_offsetY)));
					cellDetails[j - 1][i].f = fNew;
					cellDetails[j - 1][i].g = gNew;
					cellDetails[j - 1][i].h = hNew;
					cellDetails[j - 1][i].parent_i = i;
					cellDetails[j - 1][i].parent_j = j;
				}
			}
		}
	}

	return std::vector<Math::Vec2i>();
}


void AStarPathfinding::resetCalculateHeristic() {
	m_heristicFunc = [](Math::Vec2i start, Math::Vec2i end) -> f64 {
		return sqrt(pow(start.x - end.x, 2) + pow(start.y - end.y, 2));
	};
}


bool AStarPathfinding::isValid(Math::Vec2i pos) {
	pos.x += m_offsetX;
	pos.y += m_offsetY;
	return (pos.x >= 0 && pos.x < m_gridWidth && pos.y >= 0 && pos.y < m_gridHeight);
}

bool AStarPathfinding::isBlocked(Math::Vec2i pos) {
	bool isBlocked = false;

	if (!m_walkableTiles.empty() && std::find(m_walkableTiles.begin(), m_walkableTiles.end(), pos) == m_walkableTiles.end()) {
		return true;
	}
	if (std::find_if(m_obstacles.begin(), m_obstacles.end(), [pos](std::pair<u32, Math::Vec2i> pair) {
		    return pair.second.x == pos.x && pair.second.y == pos.y;
	    }) != m_obstacles.end()) {
		return true;
	}

	return isBlocked;
}

std::vector<Math::Vec2i> AStarPathfinding::tracePath(std::vector<std::vector<Cell>> cellDetails) {
	std::vector<Math::Vec2i> positions;

	i32 row = m_end.x + m_offsetX;
	i32 col = m_end.y + m_offsetY;

	while (row != cellDetails[col][row].parent_i || col != cellDetails[col][row].parent_j) {
		positions.push_back(Math::Vec2i(row - m_offsetX, col - m_offsetY));
		row = cellDetails[col][row].parent_i;
		col = cellDetails[col][row].parent_j;
	}

	i32 dirX = cellDetails[col][row].parent_i - row;
	i32 dirY = cellDetails[col][row].parent_j - col;


	positions.push_back(Math::Vec2i(row - m_offsetX, col - m_offsetY));
	std::reverse(positions.begin(), positions.end());

	std::vector<Math::Vec2i> directions;

	Math::Vec2i from = m_start;
	for (u32 i = 0; i < positions.size(); i++) {
		Math::Vec2i to = positions[i];
		i32 dirX = to.x - from.x;
		i32 dirY = to.y - from.y;

		if (dirX != 0 && dirY != 0) {
			directions.push_back(Math::Vec2i(dirX, 0));
			directions.push_back(Math::Vec2i(0, dirY));
		} else {
			directions.push_back(Math::Vec2i(dirX, dirY));
		}
		from = to;
	}
	return directions;
}
