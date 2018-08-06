#include "graph.h"

// Each edge costs 1
// Creates a vector which is like a 2D array.
// Graph is symmetric ([i][j] = [j][i])
std::vector<std::vector<unsigned int>> createGraph(unsigned int num_nodes) {
	std::vector<unsigned int> inner_vector = std::vector<unsigned int>(num_nodes, 0);
	std::vector<std::vector<unsigned int>> graph = std::vector<std::vector<unsigned int>>(num_nodes, inner_vector);
	return graph;
}

// All edges are cost of 1
void addGraphEdge(std::vector<std::vector<unsigned int>> &graph, unsigned int node_a, unsigned int node_b) {
	graph[node_a][node_b] += EDGE_COST;
	graph[node_b][node_a] += EDGE_COST;
}

std::vector<unsigned int> getNeighbours(std::vector<std::vector<unsigned int>> graph, unsigned int root_node) {
	unsigned int col_index;
	std::vector<unsigned int> neighbours;
	for (col_index = 0; col_index < graph[root_node].size(); col_index++) {
		if (graph[root_node][col_index] > 0) {
			neighbours.push_back(col_index);
		}
	}
	return neighbours;
}

bool graphHasEdge(std::vector<std::vector<unsigned int>> graph) {
	unsigned int row_index;
	unsigned int col_index;
	for (row_index = 0; row_index < graph.size(); row_index++) {
		for (col_index = 0; col_index < graph[row_index].size(); col_index++) {
			if (graph[row_index][col_index] > 0) {
				return true;
			}
		}
	}
	return false;
}

bool graphNodeHasNeighbour(std::vector<std::vector<unsigned int>> graph, unsigned int node) {
	unsigned int col_index;
	for (col_index = 0; col_index < graph[node].size(); col_index++) {
		if (graph[node][col_index] > 0) {
			return true;
		}
	}
	return false;
}

std::vector<unsigned int> getGraphNodeNieghbours(std::vector<std::vector<unsigned int>> graph, unsigned int node) {
	unsigned int col_index;
	std::vector<unsigned int> node_edges;
	for (col_index = 0; col_index < graph[node].size(); col_index++) {
		if (graph[node][col_index] > 0) {
			node_edges.push_back(col_index);
		}
	}
	return node_edges;
}
