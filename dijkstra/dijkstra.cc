#include "dijkstra.h"

unsigned int dijkstraCost(std::vector<std::vector<unsigned int>> graph, unsigned int start, unsigned int destination) {
	// Variables
	unsigned int visited_nodes;
	unsigned int node_cost[graph.size()]; // shortest distance from start to an index
	bool node_visited[graph.size()];
	unsigned int index_node;
	unsigned int min_node_value;
	unsigned int min_node;
	std::vector<unsigned int> adjacent_nodes;
	unsigned int adjacent_node_index;

	// Initialization
	// Distance from source to source is 0 and no nodes have been visited
	visited_nodes = 0;
	for (index_node = 0; index_node < graph.size(); index_node++) {
		node_cost[index_node] = INT_MAX;
		node_visited[index_node] = false;
	}
	node_cost[start] = 0;

	// Find shortest path from source to destination node while all nodes have not been visited
	while(visited_nodes < graph.size()) {
		// Get smallest unvisited node in graph
		min_node_value = INT_MAX;
		min_node;
		for (index_node = 0; index_node < graph.size(); index_node++) {
			if (node_visited[index_node] == false && (node_cost[index_node] < min_node_value)) {
				min_node_value = node_cost[index_node];
				min_node = index_node;
			}
		}

		// Early stopping condition, if min_node is destination
		if (min_node == destination) {
			break; 
		}

		// Get all adjacent nodes of current node
		adjacent_nodes = getNeighbours(graph, min_node);

		// Update optimal distance value of adjacent nodes if unvisited
		for (index_node = 0; index_node < adjacent_nodes.size(); index_node++) {
			adjacent_node_index = adjacent_nodes[index_node];
			if ((node_visited[adjacent_node_index] == false) && (node_cost[min_node] + EDGE_COST < node_cost[adjacent_node_index])) {
				node_cost[adjacent_node_index] = node_cost[min_node] + EDGE_COST;
			}
		}

		// Node is visited since all adjacent unvisited notes have been updated
		node_visited[min_node] = true;
		visited_nodes++;
	}

	return node_cost[destination];
}

// Using dijkstra, provides all of the nodes visited to get from start to destination
// Nodes given in pairs with which should share an edge, unsigned int is the cost of the edge
std::vector<unsigned int> dijkstraVisitedNodes(std::vector<std::vector<unsigned int>> graph, unsigned int start, unsigned int destination) {
	
	// Variables
	unsigned int visited_nodes;
	unsigned int node_cost[graph.size()]; // shortest distance from start to an index
	bool node_visited[graph.size()];
	unsigned int index_node;
	unsigned int min_node_value;
	unsigned int min_node;
	std::vector<unsigned int> adjacent_nodes;
	unsigned int adjacent_node_index;
	unsigned int previous_node_id[graph.size()];
	std::vector<unsigned int> optimal_path;

	// Initialization
	// Distance from source to source is 0 and no nodes have been visited
	visited_nodes = 0;
	for (index_node = 0; index_node < graph.size(); index_node++) {
		node_cost[index_node] = INT_MAX;
		node_visited[index_node] = false;
		previous_node_id[index_node] = UINT_MAX; // This means that there is no previous node id (= -1)
	}
	node_cost[start] = 0;

	// Find shortest path from source to destination node while all nodes have not been visited
	while(visited_nodes < graph.size()) {
		// Get smallest unvisited node in graph
		min_node_value = INT_MAX;
		min_node;
		for (index_node = 0; index_node < graph.size(); index_node++) {
			if (node_visited[index_node] == false && (node_cost[index_node] < min_node_value)) {
				min_node_value = node_cost[index_node];
				min_node = index_node;
			}
		}

		// Early stopping condition, if min_node is destination
		if (min_node == destination) {
			break; 
		}

		// Get all adjacent nodes of current node
		adjacent_nodes = getNeighbours(graph, min_node);

		// Update optimal distance value of adjacent nodes if unvisited
		for (index_node = 0; index_node < adjacent_nodes.size(); index_node++) {
			adjacent_node_index = adjacent_nodes[index_node];
			if ((node_visited[adjacent_node_index] == false) && (node_cost[min_node] + EDGE_COST < node_cost[adjacent_node_index])) {
				node_cost[adjacent_node_index] = node_cost[min_node] + EDGE_COST;
				previous_node_id[adjacent_node_index] = min_node;
			}
		}

		// Node is visited since all adjacent unvisited notes have been updated
		node_visited[min_node] = true;
		visited_nodes++;
	}
	
	// Return all the node pairings that should have a new edge
	// Add into vector from destination working back to source
	index_node = destination;
	optimal_path.push_back(destination);
	while (index_node != start) {
		optimal_path.push_back(previous_node_id[index_node]);
		index_node = previous_node_id[index_node];
	}

	// Reverse order of nodes (they are reversed)
	std::reverse(optimal_path.begin(), optimal_path.end());
	return optimal_path;
}