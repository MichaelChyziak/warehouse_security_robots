#include "dijkstra.h"

// Algorithm implementation based on: https://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/
unsigned int dijkstraCost(Graph *graph, Node* start, Node* destination) {
	
	// Variables
	unsigned int visited_nodes;
	unsigned int node_cost[graph->getNumNodes()]; // shortest distance from start to an index
	bool node_visited[graph->getNumNodes()];
	unsigned int index_node;
	unsigned int min_node_value;
	Node* min_node;
	std::vector<Node*> adjacent_nodes;
	unsigned int adjacent_node_index;
	unsigned int min_edge_cost;
	unsigned int current_node_cost;

	// Initialization
	// Distance from source to source is 0 and no nodes have been visited
	visited_nodes = 0;
	for (index_node = 0; index_node < graph->getNumNodes(); index_node++) {
		node_cost[index_node] = INT_MAX;
		node_visited[index_node] = false;
	}
	node_cost[start->getId()] = 0;

	// Find shortest path from source to destination node while all nodes have not been visited
	while(visited_nodes < graph->getNumNodes()) {
		// Get smallest unvisited node in graph
		min_node_value = INT_MAX;
		min_node;
		for (index_node = 0; index_node < graph->getNumNodes(); index_node++) {
			if (node_visited[index_node] == false && (node_cost[index_node] < min_node_value)) {
				min_node_value = node_cost[index_node];
				min_node = graph->getNodes()[index_node];
			}
		}

		// Get all adjacent nodes of current node
		adjacent_nodes = min_node->getNeighbours();

		// Update optimal distance value of adjacent nodes if unvisited
		for (index_node = 0; index_node < adjacent_nodes.size(); index_node++) {
			adjacent_node_index = adjacent_nodes[index_node]->getId();
			if (node_visited[adjacent_node_index] == false) {
				current_node_cost = node_cost[min_node->getId()];
				min_edge_cost = min_node->sharedEdgeMinCost(adjacent_nodes[index_node]);
				if (current_node_cost + min_edge_cost < node_cost[adjacent_node_index]) {
					node_cost[adjacent_node_index] = current_node_cost + min_edge_cost;
				}
			}
		}

		// Node is visited since all adjacent unvisited notes have been updated
		node_visited[min_node->getId()] = true;
		visited_nodes++;
	}
	
	return node_cost[destination->getId()];
}
