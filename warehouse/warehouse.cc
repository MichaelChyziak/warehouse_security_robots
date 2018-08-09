#include "warehouse.h"

std::vector<std::vector<unsigned int>> graph_robot_1;
std::vector<std::vector<unsigned int>> graph_robot_2;
std::vector<std::vector<unsigned int>> graph_robot_3;

std::vector<unsigned int> node_traversal_robot_1;
std::vector<unsigned int> node_traversal_robot_2;
std::vector<unsigned int> node_traversal_robot_3;

std::vector<std::vector<unsigned int>> warehousePatrolUpdate(unsigned int current_index) {

	std::pair<unsigned int, unsigned int> robot_1_position;
	std::pair<unsigned int, unsigned int> robot_2_position;
	std::pair<unsigned int, unsigned int> robot_3_position;

	if (graph_robot_1.empty() && graph_robot_2.empty() && graph_robot_3.empty() && node_traversal_robot_1.empty() && node_traversal_robot_2.empty() && node_traversal_robot_3.empty()) {
		graph_robot_1 = createWarehouseGraphMichael(warehouse_big_1);
		graph_robot_2 = createWarehouseGraphMichael(warehouse_big_2);
		graph_robot_3 = createWarehouseGraphMichael(warehouse_big_3);

		node_traversal_robot_1 = chinesePostman(graph_robot_1, 0);
		node_traversal_robot_2 = chinesePostman(graph_robot_2, 0);
		node_traversal_robot_3 = chinesePostman(graph_robot_3, 0);
	}

	robot_1_position = getNodeCoordinate(warehouse_big_1, node_traversal_robot_1[current_index % (node_traversal_robot_1.size() - 1)]);
	robot_2_position = getNodeCoordinate(warehouse_big_2, node_traversal_robot_2[current_index % (node_traversal_robot_2.size() - 1)]);
	robot_3_position = getNodeCoordinate(warehouse_big_3, node_traversal_robot_3[current_index % (node_traversal_robot_3.size() - 1)]);

	// Create graph again with robot locations
	std::vector< std::vector<unsigned int> > updated_warehouse = warehouse_big;
	updated_warehouse[robot_1_position.first][robot_1_position.second] = 3;
	updated_warehouse[robot_2_position.first + 4][robot_2_position.second] = 3;
	updated_warehouse[robot_3_position.first + 11][robot_3_position.second] = 3;

	return updated_warehouse;
}
