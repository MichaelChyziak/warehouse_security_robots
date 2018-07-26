#include <vector>
#include <stdio.h>
#include "graph/graph.h"
#include "chinese_postman/chinese_postman.h"

int main(int argc, char* argv[]) {

	// Create the following graph
	// Assume all edges are same cost for now (cost = 1)
	//       O       (0)
	//      / \
	//     /   \
	//    O-----O     (1, 2)
	//    |     |
	//    |     |
	//    O-----O     (3, 4)
	//    |     |
	//    |     |
	//    O-----O     (5, 6)
	//    |     |
	//    |     |
	//    O-----O     (7, 8)
	Graph *graph = new Graph(9);
	std::vector<Node*> nodes = graph->getNodes();
	graph->addEdge(nodes[0], nodes[1], 1);
	graph->addEdge(nodes[0], nodes[2], 1);
	graph->addEdge(nodes[1], nodes[2], 1);
	graph->addEdge(nodes[1], nodes[3], 1);
	graph->addEdge(nodes[2], nodes[4], 1);
	graph->addEdge(nodes[3], nodes[4], 1);
	graph->addEdge(nodes[3], nodes[5], 1);
	graph->addEdge(nodes[4], nodes[6], 1);
	graph->addEdge(nodes[5], nodes[6], 1);
	graph->addEdge(nodes[5], nodes[7], 1);
	graph->addEdge(nodes[6], nodes[8], 1);
	graph->addEdge(nodes[7], nodes[8], 1);

	// Run chinese postman algorithm
	std::vector<Node*> node_traversal;
	node_traversal = chinesePostman(graph, nodes[0]);

	// Node traversal printed output
	unsigned int index_traversal;
	printf("Node Traversal: ");
	for (index_traversal = 0; index_traversal < node_traversal.size(); index_traversal++) {
		printf("%d->", node_traversal[index_traversal]->getId());
	}
	printf("DONE\n");

	return 0;
}
