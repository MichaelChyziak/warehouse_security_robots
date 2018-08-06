#include "graphGen.h"

std::vector< std::vector<unsigned int> > createWarehouseGraph(std::vector< std::vector<unsigned int> > warehouse){
    
    std::vector< std::vector<int> > nodeCoordinates;
    unsigned int whSize = warehouse.size();

    for(int i = 0; i < whSize; i++){
        for(int j = 0; j < whSize; j++){
            if(warehouse[i][j] != OBSTACLE && warehouse[i][j] != WALL){
                nodeCoordinates.push_back({i, j, 0});
            }
        }
    }

    unsigned int numOfNodes = nodeCoordinates.size();
    std::vector<std::vector<unsigned int > > graph = createGraph(numOfNodes);

    for(int i = 0; i < numOfNodes - 1; i++){
        if(nodeCoordinates[i][0] == nodeCoordinates[i + 1][0]){
            if(nodeCoordinates[i][1] + 1 < whSize){
                if( (warehouse[nodeCoordinates[i][0]][nodeCoordinates[i][1] + 1] != OBSTACLE) && 
                    (warehouse[nodeCoordinates[i][0]][nodeCoordinates[i][1] + 1] != WALL) ){
                    //graph -> addEdge(nodes[i], nodes[i + 1], abs(nodeCoordinates[i][1] - nodeCoordinates[i + 1][1]));
                    addGraphEdge(graph, i, i + 1);
                }
            }
        }
        nodeCoordinates[i][2] = i;
    }
    nodeCoordinates[numOfNodes - 1][2] = numOfNodes - 1;

    sort(nodeCoordinates.begin(), nodeCoordinates.end(),
        [] (const std::vector<int> &a, const std::vector<int> &b){
            if(a[1] == b[1])
                return a[2] < b[2];
            else
                return a[1] < b[1];
        });
    
    for(int i = 0; i < numOfNodes - 1; i++){
        if(nodeCoordinates[i][1] == nodeCoordinates[i + 1][1]){
            if(nodeCoordinates[i][0] + 1 < whSize){
                if( (warehouse[nodeCoordinates[i][0] + 1][nodeCoordinates[i][1]] != OBSTACLE) && 
                    (warehouse[nodeCoordinates[i][0] + 1][nodeCoordinates[i][1]] != WALL) ){
                    /*graph -> addEdge(nodes[nodeCoordinates[i][2]], nodes[nodeCoordinates[i + 1][2]], 
                        abs(nodeCoordinates[i][0] - nodeCoordinates[i + 1][0]));*/
                    addGraphEdge(graph, nodeCoordinates[i][2], nodeCoordinates[i + 1][2]);
                }
            }
        }
    }

    /*for(int i = 0; i < nodeCoordinates.size(); i++){
        for(int j = 0; j < nodeCoordinates[0].size(); j++){
            std::cout << nodeCoordinates[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "\nNumber of nodes in the graph: " << graph.size() << std::endl << std::endl;
    std::vector<unsigned int> neigh;
    
    for(int i = 0; i < graph.size(); i++){
        neigh = getNeighbours(graph, i);
        std::cout << i << ": ";
        for(int j = 0; j < neigh.size(); j++){
            std::cout << neigh[j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;*/

    return graph;
}

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