#include "chinese_postman.h"

std::vector<unsigned int> chinesePostman(std::vector<std::vector<unsigned int>> graph, unsigned int start_node) {
	
	// Variables
	std::vector<unsigned int> odd_nodes;
	std::vector<std::vector<unsigned int>> odd_node_pairings; //pairings are matched together: 0 and 1, 2 and 3, etc...
	std::vector<unsigned int> best_odd_path;
	std::vector<unsigned int> missing_node_pairings; //Node pairings (index 0 and 1 is a pair, 2 and 3 a pair, etc.)
	std::vector<unsigned int> eularian_circuit;
	unsigned int index_eularian;
	unsigned int index_missing;

	odd_nodes = findOddNodes(graph);

	// If not eularian
	if (odd_nodes.size() != 0) {
		odd_node_pairings = findOddNodePairings(odd_nodes, 0);
		best_odd_path = bestOddPairingPath(graph, odd_node_pairings);
		// Make eularian by adding the edges between the following pairs of nodes with their appropriate cost
		for (index_eularian = 0; index_eularian < best_odd_path.size(); index_eularian = index_eularian + 2) {
			missing_node_pairings = dijkstraVisitedNodes(graph, best_odd_path[index_eularian], best_odd_path[index_eularian+1]);
			for (index_missing = 0; index_missing + 1 < missing_node_pairings.size(); index_missing++) {
				addGraphEdge(graph, missing_node_pairings[index_missing], missing_node_pairings[index_missing + 1]);
			}
		}
	}
	else {
		// Already is eularian, so do nothing to the graph
	}

	// Solve now since eularian graph (0 odd degree nodes)	
	eularian_circuit = getEularianCircuit(graph, start_node);

	return eularian_circuit;
}

std::vector<unsigned int> findOddNodes(std::vector<std::vector<unsigned int>> graph) {
	
	// Variables
	unsigned int graph_row_index;
	unsigned int graph_col_index;
	unsigned int edge_count;
	std::vector<unsigned int> odd_nodes;

	for (graph_row_index = 0; graph_row_index < graph.size(); graph_row_index++) {
		edge_count = 0;
		for (graph_col_index = 0; graph_col_index < graph[graph_row_index].size(); graph_col_index++) {
			edge_count += graph[graph_row_index][graph_col_index];
		}	
		if (edge_count % 2 == 1) {
			odd_nodes.push_back(graph_row_index);
		}
	}

	return odd_nodes;
}

std::vector<std::vector<unsigned int>> findOddNodePairings(std::vector<unsigned int> odd_nodes, unsigned int start_index) {

	// Variables
	std::vector<std::vector<unsigned int>> node_pairings;
	std::vector<std::vector<unsigned int>> recursive_pairings;
	std::vector<unsigned int> new_pairing;
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
std::vector<unsigned int> bestOddPairingPath(std::vector<std::vector<unsigned int>> graph, std::vector<std::vector<unsigned int>> node_pairings) {

	// Variables
	unsigned int best_cost;
	unsigned int best_node_pairing;
	unsigned int current_cost;
	unsigned int index_node_pairings;
	unsigned int index_node;
	std::unordered_map<unsigned int, unsigned int> pairing_hash_table;
	std::unordered_map<unsigned int, unsigned int>::const_iterator pairing;
	std::unordered_map<unsigned int, unsigned int>::const_iterator pairing_inverse;
	unsigned int node_pairing_1;
	unsigned int node_pairing_2;
	unsigned int dijkstra_cost;

	// initialize best_cost as worst case
	best_cost = INT_MAX;
	best_node_pairing = INT_MAX;

	// Find what node pairings provides the lowest cost
	for (index_node_pairings = 0; index_node_pairings < node_pairings.size(); index_node_pairings++) {
		current_cost = 0;
		for (index_node = 0; index_node + 1 < node_pairings[index_node_pairings].size(); index_node = index_node + 2) {
			// Search for pairing in hash table, if found take their cost from the table
			// If not found do dijkstra's and add them to hash table
			// Hash table works with node_pairing_1 * #odd nodes + node_pairing_2. This gives us unique pairings. Also have to add inverse
			node_pairing_1 = node_pairings[index_node_pairings][index_node];
			node_pairing_2 = node_pairings[index_node_pairings][index_node + 1];
			if (pairing_hash_table.count(node_pairings[0].size() * node_pairing_1 + node_pairing_2) == 1 && pairing_hash_table.count(node_pairings[0].size() * node_pairing_2 + node_pairing_1) == 1) {
				current_cost += pairing_hash_table[node_pairings[0].size() * node_pairing_1 + node_pairing_2];
			}
			else {
				dijkstra_cost = dijkstraCost(graph, node_pairing_1, node_pairing_2);
				pairing_hash_table.insert(std::make_pair(node_pairings[0].size() * node_pairing_1 + node_pairing_2, dijkstra_cost));
				pairing_hash_table.insert(std::make_pair(node_pairings[0].size() * node_pairing_2 + node_pairing_1, dijkstra_cost));
				current_cost += dijkstra_cost;
			}
		}
		if (current_cost < best_cost) {
			best_cost = current_cost;
			best_node_pairing = index_node_pairings;
		}
	}

	return node_pairings[best_node_pairing];
}

std::vector<unsigned int> getEularianCircuit(std::vector<std::vector<unsigned int>> graph, unsigned int start_node) {

	// Variables
	std::vector<unsigned int> current_path;
	std::vector<unsigned int> circuit;
	unsigned int current_node;
	unsigned int new_node;

	// Initialization
	current_node = start_node;
	current_path.push_back(current_node);

	// Create the circuit (will be in reverse format)
	while (graphHasEdge(graph) == true) {
		// Go to a random edge (0th index) and hide it from the graph
		// Continue until reach a node with no possible edges to take
		while (graphNodeHasNeighbour(graph, current_node) == true) {
			new_node = getGraphNodeNieghbours(graph, current_node)[0];
			graph[current_node][new_node]--;
			graph[new_node][current_node]--;
			current_path.push_back(new_node);
			current_node = new_node;
		}

		// Create circuit if we reach a dead end
		if (current_path.size() > 0) {
			circuit.push_back(current_path.back());
			current_path.pop_back();
			current_node = current_path.back();
		}
	}

	// Add remaining current path to circuit
	while (current_path.size() > 0) {
		circuit.push_back(current_path.back());
		current_path.pop_back();
	}

	return circuit; // This circuit is the inverse of that path to take (both are valid)
}