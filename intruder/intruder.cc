#include "intruder.h"
#include <stdio.h>
unsigned int intruder;
unsigned int robot_1 = -1;
unsigned int robot_2 = -1;
unsigned int robot_3 = -1;

// Global overall warehouse graph
std::vector<std::vector<unsigned int>> warehouse_graph;

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

	if (warehouse_with_robots[intruder_position.first][intruder_position.second] == 3) {
		intruder_caught = true;
	}

	// Create graph again with intruder location
	if (intruder_caught == false) {
		warehouse_with_robots[intruder_position.first][intruder_position.second] = 4;
	}

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

	if (warehouse_with_robots[intruder_position.first][intruder_position.second] == 3) {
		intruder_caught = true;
	}

	if (intruder_caught == false) {
		warehouse_with_robots[intruder_position.first][intruder_position.second] = 4;
	}

	return warehouse_with_robots;
}

// index must be > 0
std::vector<std::vector<unsigned int>> intruderMoveChased(unsigned int move, std::vector<std::vector<unsigned int>> &old_graph) {

	unsigned int search_depth = 10;
	std::pair<unsigned int, unsigned int> robot_1_position;
	std::pair<unsigned int, unsigned int> robot_2_position;
	std::pair<unsigned int, unsigned int> robot_3_position;
	std::vector<std::vector<unsigned int>> robot_paths;
	std::pair<unsigned int, unsigned int> intruder_position;
	unsigned int position_count;
	unsigned int nodes_counted = 0;
	unsigned int graph_index_row;
	unsigned int graph_index_col;

	// If robots just found intruder, they are not set yet
	if (robot_1 == -1 && robot_2 == -1 && robot_3 == -1) {
		// Update robot locations to be global and not local to their warehouse segment
		for (graph_index_row = 0; graph_index_row < old_graph.size(); graph_index_row++) {
			for (graph_index_col = 0; graph_index_col < old_graph[0].size(); graph_index_col++) {
				if (old_graph[graph_index_row][graph_index_col] == 0 || old_graph[graph_index_row][graph_index_col] == 4) {
					nodes_counted++;
				}
				else if (old_graph[graph_index_row][graph_index_col] == 3) {
					//nodes_counted++;
					if (robot_1 == -1) {
						robot_1 = nodes_counted;
					}
					else if (robot_2 == -1) {
						robot_2 = nodes_counted;
					}
					else { // robot_3 == -1
						robot_3 = nodes_counted;
						break;
					}
					nodes_counted++;
				}
			}
			if (robot_3 != -1) {
				break;
			} 
		}
	}
	nodes_counted = 0;

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

	if (intruder == robot_1 || intruder == robot_2 || intruder == robot_3) {
		intruder_caught = true;
	}

	// updates the robot nodes to be in their next location
	robot_1 = robot_paths[0][1];
	robot_2 = robot_paths[1][1];
	robot_3 = robot_paths[2][1];
	robot_1_position = getNodeCoordinate(warehouse_big, robot_1);
	robot_2_position = getNodeCoordinate(warehouse_big, robot_2);
	robot_3_position = getNodeCoordinate(warehouse_big, robot_3);

	if (intruder == robot_1 || intruder == robot_2 || intruder == robot_3) {
		intruder_caught = true;
	}

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
