#include "dijkstra.h"

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

		// Early stopping condition, if min_node is destination
		if (min_node == destination) {
			break; 
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

// Using dijkstra, provides all of the nodes visited to get from start to destination
// Nodes given in pairs with which should share an edge, unsigned int is the cost of the edge
std::pair<std::vector<Node*>, std::vector<unsigned int>> dijkstraVisitedNodes(Graph *graph, Node* start, Node* destination) {
	
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
	unsigned int previous_node_id[graph->getNumNodes()];
	unsigned int previous_edge_cost[graph->getNumNodes()];
	std::vector<Node*> optimal_path;
	std::vector<unsigned int> optimal_edge_costs;
	std::pair<std::vector<Node*>, std::vector<unsigned int>> nodes_cost_pair;

	// Initialization
	// Distance from source to source is 0 and no nodes have been visited
	visited_nodes = 0;
	for (index_node = 0; index_node < graph->getNumNodes(); index_node++) {
		node_cost[index_node] = INT_MAX;
		node_visited[index_node] = false;
		previous_node_id[index_node] = UINT_MAX; // This means that there is no previous node id (= -1)
		previous_edge_cost[index_node] = UINT_MAX; // Means no edge cost calculated (-1)
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
		
		// Early stopping condition, if min_node is destination
		if (min_node == destination) {
			break; 
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
					previous_node_id[adjacent_node_index] = min_node->getId();
					previous_edge_cost[adjacent_node_index] = min_edge_cost;
				}
			}
		}

		// Node is visited since all adjacent unvisited notes have been updated
		node_visited[min_node->getId()] = true;
		visited_nodes++;
	}

	// Return all the node pairings that should have a new edge
	// Add into vector from destination working back to source
	index_node = destination->getId();
	optimal_path.push_back(destination);
	while (index_node != start->getId()) {
		optimal_edge_costs.push_back(previous_edge_cost[index_node]);
		optimal_path.push_back(graph->getNodes()[previous_node_id[index_node]]);
		index_node = previous_node_id[index_node];
	}

	// Make pair and return
	nodes_cost_pair = std::make_pair(optimal_path, optimal_edge_costs);
	return nodes_cost_pair;
}
