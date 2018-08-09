#include "intruder.h"

unsigned int intruder;

std::vector<std::vector<unsigned int>> intruderStart(unsigned int start_intruder_position, unsigned int current_index) {
	std::vector<std::vector<unsigned int>> warehouse_with_robots;
	std::pair<unsigned int, unsigned int> intruder_position;

	if (start_intruder_position == 1) {
		intruder = 6;
	} 
	else if (start_intruder_position == 2) {
		intruder = 111;
	} 
	else if (start_intruder_position == 3) {
		intruder = 142;
	}
	else { // start_intruder_position == 4 or by default
		intruder = 263;
	}

	warehouse_with_robots = warehousePatrolUpdate(current_index);
	intruder_position = getNodeCoordinate(warehouse_big, intruder);

	// Create graph again with intruder location
	warehouse_with_robots[intruder_position.first][intruder_position.second] = 4;

	return warehouse_with_robots;
}

bool intruderValidMove(unsigned int move) {
	bool intruder_moved = false;
	std::pair<unsigned int, unsigned int> intruder_position;

	// intruder position before moving
	intruder_position = getNodeCoordinate(warehouse_big, intruder);

	// checks if we can move the intruder
	if (move == 1) {
		if (warehouse_big[intruder_position.first][intruder_position.second - 1] == 0) {
			intruder_moved = true;
		}
	}
	else if (move == 2) {
		if (warehouse_big[intruder_position.first][intruder_position.second + 1] == 0) {
			intruder_moved = true;
		}
	}
	else if (move == 3) {
		if (warehouse_big[intruder_position.first - 1][intruder_position.second] == 0) {
			intruder_moved = true;
		}
	}
	else if (move == 4) {
		if (warehouse_big[intruder_position.first + 1][intruder_position.second] == 0) {
			intruder_moved = true;
		}
	}

	return intruder_moved;
}

// 1 = left, 2 = right, 3 = up, 4 = down
std::vector<std::vector<unsigned int>> intruderMovePatrol(unsigned int move, unsigned int current_index) {
	std::pair<unsigned int, unsigned int> intruder_position;
	std::vector<std::vector<unsigned int>> warehouse_with_robots;
	unsigned int position_count;
	unsigned int nodes_counted = 0;

	// intruder position before moving
	intruder_position = getNodeCoordinate(warehouse_big, intruder);

	// moves intruder if possible
	if (move == 1) {
		if (warehouse_big[intruder_position.first][intruder_position.second - 1] == 0) {
			intruder = intruder - 1;
		}
	}
	else if (move == 2) {
		if (warehouse_big[intruder_position.first][intruder_position.second + 1] == 0) {
			intruder = intruder + 1;
		}
	}
	else if (move == 3) {
		if (warehouse_big[intruder_position.first - 1][intruder_position.second] == 0) {
			for (position_count = 1; position_count <= 30; position_count++) {
				if (intruder_position.second < position_count) {
					if (warehouse_big[intruder_position.first - 1][(intruder_position.second - position_count) + 30] == 0) {
						nodes_counted++;
					}
				} 
				else {
					if (warehouse_big[intruder_position.first][intruder_position.second - position_count] == 0) {
						nodes_counted++;
					}
				}
			}
		}
		intruder = intruder - nodes_counted;
	}
	else if (move == 4) {
		if (warehouse_big[intruder_position.first + 1][intruder_position.second] == 0) {
			for (position_count = 1; position_count <= 30; position_count++) {
				if (intruder_position.second + position_count > 29) {
					if (warehouse_big[intruder_position.first + 1][(intruder_position.second + position_count) % 30] == 0) {
						nodes_counted++;
					}
				} 
				else {
					if (warehouse_big[intruder_position.first][intruder_position.second + position_count] == 0) {
						nodes_counted++;
					}
				}
			}
		}
		intruder = intruder + nodes_counted;
	}

	// intruder position after NOT moving
	warehouse_with_robots = warehousePatrolUpdate(current_index);

	// Create graph again with CURRENT intruder location
	intruder_position = getNodeCoordinate(warehouse_big, intruder);
	warehouse_with_robots[intruder_position.first][intruder_position.second] = 4;

	return warehouse_with_robots;
}


bool intruderFound() {
	return false;
}