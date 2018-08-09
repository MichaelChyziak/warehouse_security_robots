#include "graphGen.h"

std::vector<std::vector<unsigned int>> createWarehouseGraphMichael(std::vector< std::vector<unsigned int>> warehouse){
    
    std::vector<std::pair<unsigned int, unsigned int>> node_coordinates; // pairs are x, y
    std::pair<unsigned int, unsigned int> coordinate_pair; // x and y coordinates
    unsigned int warehouse_row_index;
    unsigned int warehouse_col_index;
    unsigned int node_index;
    unsigned int node_matching_index;

    for(warehouse_row_index = 0; warehouse_row_index < warehouse.size(); warehouse_row_index++){
        for(warehouse_col_index = 0; warehouse_col_index < warehouse[warehouse_row_index].size(); warehouse_col_index++){
            if(warehouse[warehouse_row_index][warehouse_col_index] == PATH){
                coordinate_pair = std::make_pair(warehouse_row_index, warehouse_col_index);
                node_coordinates.push_back(coordinate_pair);
            }
        }
    }

    std::vector<std::vector<unsigned int>> graph = createGraph(node_coordinates.size());

    for (node_index = 0; node_index < node_coordinates.size(); node_index++) {
        for (node_matching_index = 1; node_matching_index < node_coordinates.size(); node_matching_index++) {
            // Check if to the left is a node, then add edge to graph
            if (node_coordinates[node_index].first == node_coordinates[node_matching_index].first && node_coordinates[node_index].second + 1 == node_coordinates[node_matching_index].second) {
                addGraphEdge(graph, node_index, node_matching_index);
            }
            // Check if below is a node, then add edge to graph
            if (node_coordinates[node_index].first + 1 == node_coordinates[node_matching_index].first && node_coordinates[node_index].second == node_coordinates[node_matching_index].second) {
                addGraphEdge(graph, node_index, node_matching_index);
            }
        }
    }

    return graph;
}