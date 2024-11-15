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

	m_gridWidth = abs(m_end.x - m_start.x);
	m_gridHeight = abs(m_end.y - m_start.y);
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


std::vector<Math::Vec2i> AStarPathfinding::getPath() {
	if (!isValid(m_start) || !isValid(m_end)) { return {}; }
	if (isBlocked(m_end)) { return {}; }

	bool closedList[m_gridWidth][m_gridHeight];

	std::memset(closedList, false, sizeof(closedList));

	Cell cellDetails[m_gridWidth][m_gridHeight];

	for (u32 j = 0; j < m_gridHeight; ++j) {
		for (u32 i = 0; i < m_gridWidth; ++i) {
			cellDetails[i][j].f = std::numeric_limits<f32>().max();
			cellDetails[i][j].g = std::numeric_limits<f32>().max();
			cellDetails[i][j].h = std::numeric_limits<f32>().max();
			cellDetails[i][j].parent_i = i;
			cellDetails[i][j].parent_j = j;
		}
	}

	u32 i = m_start.x, j = m_start.y;
	cellDetails[i][j].f = 0;
	cellDetails[i][j].g = 0;
	cellDetails[i][j].h = 0;
	cellDetails[i][j].parent_i = i;
	cellDetails[i][j].parent_j = j;


	std::set<std::pair<f64, Math::Vec2i>> openList;

	openList.insert(std::make_pair(0.0, Math::Vec2i(m_start.x, m_start.y)));

	while (!openList.empty()) {
		std::pair<f64, Math::Vec2i> p = *openList.begin();
		openList.erase(openList.begin());

		i = p.second.x;
		j = p.second.y;
		closedList[i][j] = true;

		double gNew, hNew, fNew;

		// Successor 1 (North)
		if (isValid(Math::Vec2i(i - 1, j))) {
			if ((i - 1) == m_end.x && j == m_end.y) {
				cellDetails[i - 1][j].parent_i = i;
				cellDetails[i - 1][j].parent_j = j;
				return tracePath(&cellDetails[0][0]);
			} else if (!closedList[i - 1][j] && !isBlocked(Math::Vec2i(i - 1, j))) {
				gNew = cellDetails[i][j].g + 1.f;
				hNew = m_heristicFunc(Math::Vec2i(i - 1, j), m_end);
				fNew = gNew + hNew;

				if (cellDetails[i - 1][j].f == std::numeric_limits<f32>().max() || cellDetails[i - 1][j].f > fNew) {
					openList.insert(std::make_pair(fNew, Math::Vec2i(i - 1, j)));
					cellDetails[i - 1][j].f = fNew;
					cellDetails[i - 1][j].g = gNew;
					cellDetails[i - 1][j].h = hNew;
					cellDetails[i - 1][j].parent_i = i;
					cellDetails[i - 1][j].parent_j = j;
				}
			}
		}

		// Successor 2 (South)
		if (isValid(Math::Vec2i(i + 1, j))) {
			if ((i + 1) == m_end.x && j == m_end.y) {
				cellDetails[i + 1][j].parent_i = i;
				cellDetails[i + 1][j].parent_j = j;
				return tracePath(&cellDetails[0][0]);
			} else if (!closedList[i + 1][j] && !isBlocked(Math::Vec2i(i + 1, j))) {
				gNew = cellDetails[i][j].g + 1.f;
				hNew = m_heristicFunc(Math::Vec2i(i + 1, j), m_end);
				fNew = gNew + hNew;

				if (cellDetails[i + 1][j].f == std::numeric_limits<f32>().max() || cellDetails[i + 1][j].f > fNew) {
					openList.insert(std::make_pair(fNew, Math::Vec2i(i + 1, j)));
					cellDetails[i + 1][j].f = fNew;
					cellDetails[i + 1][j].g = gNew;
					cellDetails[i + 1][j].h = hNew;
					cellDetails[i + 1][j].parent_i = i;
					cellDetails[i + 1][j].parent_j = j;
				}
			}
		}

		// Successor 3 (East)
		if (isValid(Math::Vec2i(i, j + 1))) {
			if (i == m_end.x && (j + 1) == m_end.y) {
				cellDetails[i][j + 1].parent_i = i;
				cellDetails[i][j + 1].parent_j = j;
				return tracePath(&cellDetails[0][0]);
			} else if (!closedList[i][j + 1] && !isBlocked(Math::Vec2i(i, j + 1))) {
				gNew = cellDetails[i][j].g + 1.f;
				hNew = m_heristicFunc(Math::Vec2i(i, j + 1), m_end);
				fNew = gNew + hNew;

				if (cellDetails[i][j + 1].f == std::numeric_limits<f32>().max() || cellDetails[i][j + 1].f > fNew) {
					openList.insert(std::make_pair(fNew, Math::Vec2i(i, j + 1)));
					cellDetails[i][j + 1].f = fNew;
					cellDetails[i][j + 1].g = gNew;
					cellDetails[i][j + 1].h = hNew;
					cellDetails[i][j + 1].parent_i = i;
					cellDetails[i][j + 1].parent_j = j;
				}
			}
		}

		// Successor 4 (West)
		if (isValid(Math::Vec2i(i, j - 1))) {
			if (i == m_end.x && (j - 1) == m_end.y) {
				cellDetails[i][j - 1].parent_i = i;
				cellDetails[i][j - 1].parent_j = j;
				return tracePath(&cellDetails[0][0]);
			} else if (!closedList[i][j - 1] && !isBlocked(Math::Vec2i(i, j - 1))) {
				gNew = cellDetails[i][j].g + 1.f;
				hNew = m_heristicFunc(Math::Vec2i(i, j - 1), m_end);
				fNew = gNew + hNew;

				if (cellDetails[i][j - 1].f == std::numeric_limits<f32>().max() || cellDetails[i][j - 1].f > fNew) {
					openList.insert(std::make_pair(fNew, Math::Vec2i(i, j - 1)));
					cellDetails[i][j - 1].f = fNew;
					cellDetails[i][j - 1].g = gNew;
					cellDetails[i][j - 1].h = hNew;
					cellDetails[i][j - 1].parent_i = i;
					cellDetails[i][j - 1].parent_j = j;
				}
			}
		}

		// Successor 5 (North-East)
		if (isValid(Math::Vec2i(i - 1, j + 1))) {
			if ((i - 1) == m_end.x && (j + 1) == m_end.y) {
				cellDetails[i - 1][j + 1].parent_i = i;
				cellDetails[i - 1][j + 1].parent_j = j;
				return tracePath(&cellDetails[0][0]);
			} else if (closedList[i - 1][j + 1] && !isBlocked(Math::Vec2i(i - 1, j + 1))) {
				gNew = cellDetails[i][j].g + 1.f;
				hNew = m_heristicFunc(Math::Vec2i(i - 1, j + 1), m_end);
				fNew = gNew + hNew;

				if (cellDetails[i - 1][j + 1].f == std::numeric_limits<f32>().max() || cellDetails[i - 1][j + 1].f > fNew) {
					openList.insert(std::make_pair(fNew, Math::Vec2i(i - 1, j + 1)));
					cellDetails[i - 1][j + 1].f = fNew;
					cellDetails[i - 1][j + 1].g = gNew;
					cellDetails[i - 1][j + 1].h = hNew;
					cellDetails[i - 1][j + 1].parent_i = i;
					cellDetails[i - 1][j + 1].parent_j = j;
				}
			}
		}

		// Successor 6 (North-West)
		if (isValid(Math::Vec2i(i - 1, j - 1))) {
			if ((i - 1) == m_end.x && (j - 1) == m_end.y) {
				cellDetails[i - 1][j - 1].parent_i = i;
				cellDetails[i - 1][j - 1].parent_j = j;
				return tracePath(&cellDetails[0][0]);
			} else if (!closedList[i - 1][j - 1] && !isBlocked(Math::Vec2i(i - 1, j - 1))) {
				gNew = cellDetails[i][j].g + 1.f;
				hNew = m_heristicFunc(Math::Vec2i(i - 1, j - 1), m_end);
				fNew = gNew + hNew;

				if (cellDetails[i - 1][j - 1].f == std::numeric_limits<f32>().max() || cellDetails[i - 1][j - 1].f > fNew) {
					openList.insert(std::make_pair(fNew, Math::Vec2i(i - 1, j - 1)));
					cellDetails[i - 1][j - 1].f = fNew;
					cellDetails[i - 1][j - 1].g = gNew;
					cellDetails[i - 1][j - 1].h = hNew;
					cellDetails[i - 1][j - 1].parent_i = i;
					cellDetails[i - 1][j - 1].parent_j = j;
				}
			}
		}

		// Successor 7 (North-East)
		if (isValid(Math::Vec2i(i + 1, j + 1))) {
			if ((i + 1) == m_end.x && (j + 1) == m_end.y) {
				cellDetails[i + 1][j + 1].parent_i = i;
				cellDetails[i + 1][j + 1].parent_j = j;
				return tracePath(&cellDetails[0][0]);
			} else if (!closedList[i + 1][j + 1] && !isBlocked(Math::Vec2i(i + 1, j + 1))) {
				gNew = cellDetails[i][j].g + 1.f;
				hNew = m_heristicFunc(Math::Vec2i(i + 1, j + 1), m_end);
				fNew = gNew + hNew;

				if (cellDetails[i + 1][j + 1].f == std::numeric_limits<f32>().max() || cellDetails[i + 1][j + 1].f > fNew) {
					openList.insert(std::make_pair(fNew, Math::Vec2i(i + 1, j + 1)));
					cellDetails[i + 1][j + 1].f = fNew;
					cellDetails[i + 1][j + 1].g = gNew;
					cellDetails[i + 1][j + 1].h = hNew;
					cellDetails[i + 1][j + 1].parent_i = i;
					cellDetails[i + 1][j + 1].parent_j = j;
				}
			}
		}

		// Successor 8 (South-West)
		if (isValid(Math::Vec2i(i + 1, j - 1))) {
			if ((i + 1) == m_end.x && (j - 1) == m_end.y) {
				cellDetails[i + 1][j - 1].parent_i = i;
				cellDetails[i + 1][j - 1].parent_j = j;
				return tracePath(&cellDetails[0][0]);
			} else if (!closedList[i + 1][j - 1] && !isBlocked(Math::Vec2i(i + 1, j - 1))) {
				gNew = cellDetails[i][j].g + 1.f;
				hNew = m_heristicFunc(Math::Vec2i(i + 1, j - 1), m_end);
				fNew = gNew + hNew;

				if (cellDetails[i + 1][j + 1].f == std::numeric_limits<f32>().max() || cellDetails[i + 1][j + 1].f > fNew) {
					openList.insert(std::make_pair(fNew, Math::Vec2i(i + 1, j - 1)));
					cellDetails[i + 1][j - 1].f = fNew;
					cellDetails[i + 1][j - 1].g = gNew;
					cellDetails[i + 1][j - 1].h = hNew;
					cellDetails[i + 1][j - 1].parent_i = i;
					cellDetails[i + 1][j - 1].parent_j = j;
				}
			}
		}
	}

	return std::vector<Math::Vec2i>();
}


bool AStarPathfinding::isValid(Math::Vec2i pos) {
	return (pos.x >= 0 && pos.x < m_gridWidth && pos.y >= 0 && pos.y < m_gridHeight);
}

bool AStarPathfinding::isBlocked(Math::Vec2i pos) {
	bool grid[m_gridWidth][m_gridHeight];
	std::memset(grid, false, sizeof(grid));

	bool isBlocked = false;

	if (!m_walkableTiles.empty()) {
		if (std::find_if(m_walkableTiles.begin(), m_walkableTiles.end(),
		                 [pos](Math::Vec2i tile) { return tile.x == pos.x && tile.y == pos.y; }) == m_walkableTiles.end()) {
			isBlocked = true;
		}
	}

	if (!m_obstacles.empty()) {
		if (std::find_if(m_obstacles.begin(), m_obstacles.end(), [pos](std::pair<u32, Math::Vec2i> pair) {
			    return pair.second.x == pos.x && pair.second.y == pos.y;
		    }) != m_obstacles.end()) {
			isBlocked = true;
		}
	}

	return isBlocked;
}
