#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

const unsigned int EDGE_COST = 1;

std::vector<std::vector<unsigned int>> createGraph(unsigned int num_nodes);
void addGraphEdge(std::vector<std::vector<unsigned int>> &graph, unsigned int node_a, unsigned int node_b);
std::vector<unsigned int> getNeighbours(std::vector<std::vector<unsigned int>> graph, unsigned int root_node);
bool graphHasEdge(std::vector<std::vector<unsigned int>> graph);
bool graphNodeHasNeighbour(std::vector<std::vector<unsigned int>> graph, unsigned int node);
std::vector<unsigned int> getGraphNodeNieghbours(std::vector<std::vector<unsigned int>> graph, unsigned int node);
std::pair<unsigned int, unsigned int> getNodeCoordinate(std::vector<std::vector<unsigned int>> warehouse, unsigned int node);

#endif // GRAPH_H
