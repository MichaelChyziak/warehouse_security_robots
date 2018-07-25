#include "chinese_postman.h"
#include <stdio.h> //TODO REMOVE

void chinesePostman(Graph *graph) {
	
	// Variables
	std::vector<Node*> odd_nodes;
	std::vector<std::vector<Node*>> odd_node_pairings;
	std::vector<Node*> best_odd_path;

	odd_nodes = findOddNodes(graph->getNodes(), graph->getNumNodes());

	if (odd_nodes.size() != 0) {
		odd_node_pairings = findOddNodePairings(odd_nodes, 0);
		best_odd_path = bestOddPairingPath(graph, odd_node_pairings);
		// TODO make eularian
	}
	
	// TODO solve since now eularian
}

std::vector<Node*> findOddNodes(std::vector<Node*> nodes, unsigned int num_nodes) {
	
	// Variables
	int node_index;
	std::vector<Node*> odd_nodes;

	for (node_index = 0; node_index < num_nodes; node_index++) {
		// Check if the node is even or odd degree (even or odd number of edges)
		if (nodes[node_index]->getNumEdges() % 2 != 0) {
			odd_nodes.push_back(nodes[node_index]);
		}
	}

	return odd_nodes;
}

std::vector<std::vector<Node*>> findOddNodePairings(std::vector<Node*> odd_nodes, unsigned int start_index) {

	// Variables
	std::vector<std::vector<Node*>> node_pairings;
	std::vector<std::vector<Node*>> recursive_pairings;
	std::vector<Node*> new_pairing;
	unsigned int index_swapper = start_index + 1;
	unsigned int index_swappee;

	// Stopping condition
	if (start_index == odd_nodes.size() - 2) {
		node_pairings.push_back(odd_nodes);
		return node_pairings;
	}

	// Swap with itself and then increment swap, then call self (recursively)
	for (index_swappee = index_swapper; index_swappee < odd_nodes.size(); index_swappee++) {
		new_pairing = odd_nodes;

		// Swap and recursive call
		std::swap(new_pairing[index_swapper], new_pairing[index_swappee]);
		recursive_pairings = findOddNodePairings(new_pairing, start_index + 2);
		node_pairings.insert(node_pairings.end(), recursive_pairings.begin(), recursive_pairings.end());
	}

	return node_pairings;
}

// Cannot pass empty graph and/or node_pairings
std::vector<Node*> bestOddPairingPath(Graph *graph, std::vector<std::vector<Node*>> node_pairings) {
	
	// Variables
	unsigned int best_cost;
	unsigned int best_node_pairing;
	unsigned int current_cost;
	unsigned int index_node_pairings;
	unsigned int index_node;

	// initialize best_cost as worst case
	best_cost = INT_MAX;
	best_node_pairing = INT_MAX;

	// Find what node pairings provides the lowest cost
	for (index_node_pairings = 0; index_node_pairings + 1 < node_pairings.size(); index_node_pairings++) {
		current_cost = 0;
		for (index_node = 0; index_node < node_pairings[index_node_pairings].size(); index_node = index_node + 2) {
			current_cost += dijkstraCost(graph, node_pairings[index_node_pairings][index_node], node_pairings[index_node_pairings][index_node + 1]);
		}
		if (current_cost < best_cost) {
			best_cost = current_cost;
			best_node_pairing = index_node_pairings;
		}
	}

	return node_pairings[best_node_pairing];
}
