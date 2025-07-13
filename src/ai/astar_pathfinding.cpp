#include <set>

#include <LTEngine/exceptions/exc_not_possible.hpp>

#include <LTEngine/ai/astar_pathfinding.hpp>


using namespace LTEngine;
using namespace LTEngine::AI;


AStarPathfinding::AStarPathfinding() {
	reset_calculate_heristic();
}


void AStarPathfinding::set_path(Math::Vec2i start, Math::Vec2i end) {
	_start = start;
	_end = end;

	// Initialize grid dimensions and offsets
	_offset_x = 0;
	_offset_y = 0;

	// Determine minimum and maximum coordinates
	int min_x = std::min(_start.x, _end.x);
	int min_y = std::min(_start.y, _end.y);
	int max_x = std::max(_start.x, _end.x);
	int max_y = std::max(_start.y, _end.y);

	// Check for negative coordinates and adjust grid size
	if (min_x < 0) {
		_offset_x = -min_x;               // Offset for negative X
		_grid_width = (max_x - min_x) * 2; // Double grid size on X-axis
	} else {
		_grid_width = max_x - min_x + 1; // Normal size
	}

	if (min_y < 0) {
		_offset_y = -min_y;                // Offset for negative Y
		_grid_height = (max_y - min_y) * 2; // Double grid size on Y-axis
	} else {
		_grid_height = max_y - min_y + 1; // Normal size
	}
}

bool AStarPathfinding::is_possible_to_reach_in_theory() {
	if (!_is_valid(_start) || !_is_valid(_end)) {
		return false;
	}
	if (_is_blocked(_end)) {
		return false;
	}
	return true;
}


void AStarPathfinding::set_walkable_path(std::vector<Math::Vec2i> path) {
	_walkable_tiles = path;
}


u32 AStarPathfinding::add_obstacle(Math::Vec2i pos) {
	u32 id = _next_obstacle_id++;
	_obstacles[id] = pos;
	return id;
}

void AStarPathfinding::remove_obstacle(u32 id) {
	_obstacles.erase(id);
}


std::vector<Math::Vec2i> AStarPathfinding::calculate_path() {
	if (!_is_valid(_start) || !_is_valid(_end)) {
		return {};
	}
	if (_is_blocked(_end)) {
		return {};
	}

	std::vector<std::vector<bool>> closed_list(_grid_height, std::vector<bool>(_grid_width, false));
	std::vector<std::vector<Cell>> cell_details(_grid_height, std::vector<Cell>(_grid_width));

	for (u32 i = 0; i < _grid_width; ++i) {
		for (u32 j = 0; j < _grid_height; ++j) {
			cell_details[j][i].f = std::numeric_limits<i32>().max();
			cell_details[j][i].g = std::numeric_limits<i32>().max();
			cell_details[j][i].h = std::numeric_limits<i32>().max();
			cell_details[j][i].parent_i = i;
			cell_details[j][i].parent_j = j;
		}
	}

	u32 i = _start.x + _offset_x, j = _start.y + _offset_y;
	cell_details[j][i].f = 0;
	cell_details[j][i].g = 0;
	cell_details[j][i].h = 0;
	cell_details[j][i].parent_i = i;
	cell_details[j][i].parent_j = j;


	std::set<std::pair<f32, Math::Vec2i>> open_list;

	open_list.insert(std::make_pair(0.0, Math::Vec2i(_start.x, _start.y)));

	while (!open_list.empty()) {
		std::pair<f32, Math::Vec2i> p = *open_list.begin();
		open_list.erase(open_list.begin());

		i = p.second.x + _offset_x;
		j = p.second.y + _offset_y;
		closed_list[j][i] = true;

		f64 g_new, h_new, f_new;

		// Successor 1 (Right)
		if (_is_valid(Math::Vec2i(i - 1 - _offset_x, j - _offset_y))) {
			if ((i - 1 - _offset_x) == _end.x && j - _offset_y == _end.y) {
				cell_details[j][i - 1].parent_i = i;
				cell_details[j][i - 1].parent_j = j;
				return _trace_path(cell_details);
			} else if (!closed_list[j][i - 1] && !_is_blocked(Math::Vec2i(i - 1 - _offset_x, j - _offset_y))) {
				g_new = cell_details[j][i].g + 1.f;
				h_new = _heristic_func(Math::Vec2i(i - 1, j), _end);
				f_new = g_new + h_new;

				if (cell_details[j][i - 1].f == std::numeric_limits<i32>().max() || cell_details[j][i - 1].f > f_new) {
					open_list.insert(std::make_pair(f_new, Math::Vec2i(i - 1 - _offset_x, j - _offset_y)));
					cell_details[j][i - 1].f = f_new;
					cell_details[j][i - 1].g = g_new;
					cell_details[j][i - 1].h = h_new;
					cell_details[j][i - 1].parent_i = i;
					cell_details[j][i - 1].parent_j = j;
				}
			}
		}

		// Successor 2 (Left)
		if (_is_valid(Math::Vec2i(i + 1 - _offset_x, j - _offset_y))) {
			if ((i + 1 - _offset_x) == _end.x && j - _offset_y == _end.y) {
				cell_details[j][i + 1].parent_i = i;
				cell_details[j][i + 1].parent_j = j;
				return _trace_path(cell_details);
			} else if (!closed_list[j][i + 1] && !_is_blocked(Math::Vec2i(i + 1 - _offset_x, j - _offset_y))) {
				g_new = cell_details[j][i].g + 1.f;
				h_new = _heristic_func(Math::Vec2i(i + 1, j), _end);
				f_new = g_new + h_new;

				if (cell_details[j][i + 1].f == std::numeric_limits<i32>().max() || cell_details[j][i + 1].f > f_new) {
					open_list.insert(std::make_pair(f_new, Math::Vec2i(i + 1 - _offset_x, j - _offset_y)));
					cell_details[j][i + 1].f = f_new;
					cell_details[j][i + 1].g = g_new;
					cell_details[j][i + 1].h = h_new;
					cell_details[j][i + 1].parent_i = i;
					cell_details[j][i + 1].parent_j = j;
				}
			}
		}

		// Successor 3 (Down)
		if (_is_valid(Math::Vec2i(i - _offset_x, j + 1 - _offset_y))) {
			if (i - _offset_x == _end.x && (j + 1 - _offset_y) == _end.y) {
				cell_details[j + 1][i].parent_i = i;
				cell_details[j + 1][i].parent_j = j;
				return _trace_path(cell_details);
			} else if (!closed_list[j + 1][i] && !_is_blocked(Math::Vec2i(i - _offset_x, j + 1 - _offset_y))) {
				g_new = cell_details[j][i].g + 1.f;
				h_new = _heristic_func(Math::Vec2i(i, j + 1), _end);
				f_new = g_new + h_new;

				if (cell_details[j + 1][i].f == std::numeric_limits<i32>().max() || cell_details[j + 1][i].f > f_new) {
					open_list.insert(std::make_pair(f_new, Math::Vec2i(i - _offset_x, j + 1 - _offset_y)));
					cell_details[j + 1][i].f = f_new;
					cell_details[j + 1][i].g = g_new;
					cell_details[j + 1][i].h = h_new;
					cell_details[j + 1][i].parent_i = i;
					cell_details[j + 1][i].parent_j = j;
				}
			}
		}

		// Successor 4 (Up)
		if (_is_valid(Math::Vec2i(i - _offset_x, j - 1 - _offset_y))) {
			if (i - _offset_x == _end.x && (j - 1 - _offset_y) == _end.y) {
				cell_details[j - 1][i].parent_i = i;
				cell_details[j - 1][i].parent_j = j;
				return _trace_path(cell_details);
			} else if (!closed_list[j - 1][i] && !_is_blocked(Math::Vec2i(i - _offset_x, j - 1 - _offset_y))) {
				g_new = cell_details[j][i].g + 1.f;
				h_new = _heristic_func(Math::Vec2i(i - _offset_x, j - 1 - _offset_y), _end);
				f_new = g_new + h_new;

				if (cell_details[j - 1][i].f == std::numeric_limits<i32>().max() || cell_details[j - 1][i].f > f_new) {
					open_list.insert(std::make_pair(f_new, Math::Vec2i(i - _offset_x, j - 1 - _offset_y)));
					cell_details[j - 1][i].f = f_new;
					cell_details[j - 1][i].g = g_new;
					cell_details[j - 1][i].h = h_new;
					cell_details[j - 1][i].parent_i = i;
					cell_details[j - 1][i].parent_j = j;
				}
			}
		}
	}

	throw NotPossibleException("No Path Found");
}


void AStarPathfinding::reset_calculate_heristic() {
	_heristic_func = [](Math::Vec2i start, Math::Vec2i end) -> f64 {
		return sqrt(pow(start.x - end.x, 2) + pow(start.y - end.y, 2));
	};
}


bool AStarPathfinding::_is_valid(Math::Vec2i pos) {
	pos.x += _offset_x;
	pos.y += _offset_y;
	return (pos.x >= 0 && pos.x < _grid_width && pos.y >= 0 && pos.y < _grid_height);
}

bool AStarPathfinding::_is_blocked(Math::Vec2i pos) {
	bool is_blocked = false;

	if (!_walkable_tiles.empty() && std::find(_walkable_tiles.begin(), _walkable_tiles.end(), pos) == _walkable_tiles.end()) {
		return true;
	}
	if (std::find_if(_obstacles.begin(), _obstacles.end(), [pos](std::pair<u32, Math::Vec2i> pair) {
		    return pair.second.x == pos.x && pair.second.y == pos.y;
	    }) != _obstacles.end()) {
		return true;
	}

	return is_blocked;
}

std::vector<Math::Vec2i> AStarPathfinding::_trace_path(std::vector<std::vector<Cell>> cell_details) {
	std::vector<Math::Vec2i> positions;

	i32 row = _end.x + _offset_x;
	i32 col = _end.y + _offset_y;

	while (row != cell_details[col][row].parent_i || col != cell_details[col][row].parent_j) {
		positions.push_back(Math::Vec2i(row - _offset_x, col - _offset_y));
		row = cell_details[col][row].parent_i;
		col = cell_details[col][row].parent_j;
	}

	i32 dir_x = cell_details[col][row].parent_i - row;
	i32 dir_y = cell_details[col][row].parent_j - col;


	positions.push_back(Math::Vec2i(row - _offset_x, col - _offset_y));
	std::reverse(positions.begin(), positions.end());

	std::vector<Math::Vec2i> directions;

	Math::Vec2i from = _start;
	for (u32 i = 0; i < positions.size(); i++) {
		Math::Vec2i to = positions[i];
		i32 dir_x = to.x - from.x;
		i32 dir_y = to.y - from.y;

		if (dir_x != 0 && dir_y != 0) {
			directions.push_back(Math::Vec2i(dir_x, 0));
			directions.push_back(Math::Vec2i(0, dir_y));
		} else {
			directions.push_back(Math::Vec2i(dir_x, dir_y));
		}
		from = to;
	}
	return directions;
}
