#include "intruder.h"

unsigned int intruder;
unsigned int robot_1 = -1;
unsigned int robot_2 = -1;
unsigned int robot_3 = -1;

// Global overall warehouse graph
std::vector<std::vector<unsigned int>> warehouse_graph;

// Make externals we can borrow
extern std::vector<unsigned int> node_traversal_robot_1;
extern std::vector<unsigned int> node_traversal_robot_2;
extern std::vector<unsigned int> node_traversal_robot_3;

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

	// robot positions after moving
	warehouse_with_robots = warehousePatrolUpdate(current_index);

	// Create graph again with updated intruder location
	intruder_position = getNodeCoordinate(warehouse_big, intruder);
	warehouse_with_robots[intruder_position.first][intruder_position.second] = 4;

	return warehouse_with_robots;
}

// index must be > 0
std::vector<std::vector<unsigned int>> intruderMoveChased(unsigned int move, unsigned int index) {
	unsigned int search_depth = 10;
	std::pair<unsigned int, unsigned int> robot_1_position;
	std::pair<unsigned int, unsigned int> robot_2_position;
	std::pair<unsigned int, unsigned int> robot_3_position;
	std::vector<std::vector<unsigned int>> robot_paths;
	std::pair<unsigned int, unsigned int> intruder_position;
	unsigned int position_count;
	unsigned int nodes_counted = 0;

	// If robots just found intruder, they are not set yet
	if (robot_1 == -1 && robot_2 == -1 && robot_3 == -1) {
		robot_1 = node_traversal_robot_1[index];
		robot_2 = node_traversal_robot_2[index];
		robot_3 = node_traversal_robot_3[index];
	}

	// Create warehouse_graph if not already
	if (warehouse_graph.empty() == true) {
		warehouse_graph = createWarehouseGraphMichael(warehouse_big);	
	}
	robot_paths = controlRobots(warehouse_graph, robot_1, robot_2, robot_3, intruder, search_depth);

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

	// updates the robot nodes to be in their next location
	robot_1 = robot_paths[0][1];
	robot_2 = robot_paths[1][1];
	robot_3 = robot_paths[2][1];
	robot_1_position = getNodeCoordinate(warehouse_big, robot_1);
	robot_2_position = getNodeCoordinate(warehouse_big, robot_2);
	robot_3_position = getNodeCoordinate(warehouse_big, robot_3);

	// Create graph again with robot locations
	std::vector<std::vector<unsigned int>> updated_warehouse = warehouse_big;
	updated_warehouse[robot_1_position.first][robot_1_position.second] = 3;
	updated_warehouse[robot_2_position.first][robot_2_position.second] = 3;
	updated_warehouse[robot_3_position.first][robot_3_position.second] = 3;

	// Create graph again with updated intruder location
	intruder_position = getNodeCoordinate(warehouse_big, intruder);
	updated_warehouse[intruder_position.first][intruder_position.second] = 4;

	return updated_warehouse;
}

bool intruderFound(std::vector<std::vector<unsigned int>> updatedWarehouseLayout) {

	bool wasFound = false;
	std::pair<unsigned int, unsigned int> intruderCoortinate = getNodeCoordinate(warehouse_big, intruder);

	for(int i = 0; i <= vision; i++){
		//check left
		if((int)intruderCoortinate.second - i > 0){
			if(updatedWarehouseLayout[intruderCoortinate.first][intruderCoortinate.second - i] == WALL || 
				updatedWarehouseLayout[intruderCoortinate.first][intruderCoortinate.second - i] == DOOR){
				break;
			} else if(updatedWarehouseLayout[intruderCoortinate.first][intruderCoortinate.second - i] == ROBOT){
				wasFound = true;
				return wasFound;
			}
		}
	}
	
	for(int i = 0; i <= vision; i++){
		//check right
		if(intruderCoortinate.second + i < updatedWarehouseLayout[0].size()){
			if(updatedWarehouseLayout[intruderCoortinate.first][intruderCoortinate.second + i] == WALL || 
				updatedWarehouseLayout[intruderCoortinate.first][intruderCoortinate.second + i] == DOOR){
				break;
			} else if(updatedWarehouseLayout[intruderCoortinate.first][intruderCoortinate.second + i] == ROBOT){
				wasFound = true;
				return wasFound;
			}
		}
	}

	for(int i = 0; i <= vision; i++){
		//check up
		if((int)intruderCoortinate.first - i > 0){
			if(updatedWarehouseLayout[intruderCoortinate.first - i][intruderCoortinate.second] == WALL || 
				updatedWarehouseLayout[intruderCoortinate.first - i][intruderCoortinate.second] == DOOR){
				break;
			} else if(updatedWarehouseLayout[intruderCoortinate.first - i][intruderCoortinate.second] == ROBOT){
				wasFound = true;
				return wasFound;
			}
		}
	}

	for(int i = 0; i <= vision; i++){
		//check down
		if((int)intruderCoortinate.first + i < updatedWarehouseLayout.size()){
			if(updatedWarehouseLayout[intruderCoortinate.first + i][intruderCoortinate.second] == WALL || 
				updatedWarehouseLayout[intruderCoortinate.first + i][intruderCoortinate.second] == DOOR){
				break;
			} else if(updatedWarehouseLayout[intruderCoortinate.first + i][intruderCoortinate.second] == ROBOT){
				wasFound = true;
				return wasFound;
			}
		}
	}

	return wasFound;
}