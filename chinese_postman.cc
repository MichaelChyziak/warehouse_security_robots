#include "chinese_postman.h"

void chinesePostman(Graph *graph) {

	findNumberOddNodes(graph->getNodes(), graph->getNumNodes());
	// TODO
}

vector<Edge*> findOddNodes(vector<Node*> nodes, unsigned int num_nodes) {

	// Variables
	int node_index;
	vector<Node*> odd_nodes;

	for (node_index = 0; node_index < num_nodes; node_index++) {
		// Check if the node is even or odd degree (even or odd number of edges)
		if (nodes.at(node_index)->getNumEdges() % 2 != 0) {
			odd_nodes.push_back(nodes.at(node_index))
		}
	}

	return odd_nodes;
}

