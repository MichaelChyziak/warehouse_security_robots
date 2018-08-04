#include <stdio.h>
#include "graph/graph.h"
#include "chinese_postman/chinese_postman.h"

int main(int argc, char* argv[]) {

	// FIRST DEMO
	// Create the following graph
	// Edges are of cost 1 (for now)
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
	std::vector<std::vector<unsigned int>> graph = createGraph(9);
	addGraphEdge(graph, 0, 1);
	addGraphEdge(graph, 0, 2);
	addGraphEdge(graph, 1, 2);
	addGraphEdge(graph, 1, 3);
	addGraphEdge(graph, 2, 4);
	addGraphEdge(graph, 3, 4);
	addGraphEdge(graph, 3, 5);
	addGraphEdge(graph, 4, 6);
	addGraphEdge(graph, 5, 6);
	addGraphEdge(graph, 5, 7);
	addGraphEdge(graph, 6, 8);
	addGraphEdge(graph, 7, 8);

	// Run chinese postman algorithm
	std::vector<unsigned int> node_traversal;;
	node_traversal = chinesePostman(graph, 0);

	// Node traversal printed output
	unsigned int index_traversal;
	printf("Node Traversal: ");
	for (index_traversal = 0; index_traversal < node_traversal.size(); index_traversal++) {
		printf("%d->", node_traversal[index_traversal]);
	}
	printf("DONE\n");

	// SECOND DEMO (NODES EVERYWHERE AND EDGES ARE OF COST 1)
	// Create the following graph
	//       O       (0)
	//      O O	 	 (1, 2)
	//     O   O	 (3, 4)
	//    OOOOOOO    (5, 6, 7, 8, 9, 10, 11)
	//    O     O	 (12, 13)
	//    O     O	 (14, 15)
	//    OOOOOOO    (16, 17, 18, 19, 20, 21, 22)
	//    O     O	 (23, 24)
	//    O     O	 (25, 26)
	//    OOOOOOO    (27, 28, 29, 30, 31, 32, 33)
	//    O     O	 (34, 35)
	//    O     O	 (36, 37)
	//    OOOOOOO    (38, 39, 40, 41, 42, 43, 44)
	std::vector<std::vector<unsigned int>> graph2 = createGraph(45);
	addGraphEdge(graph2, 0, 1);
	addGraphEdge(graph2, 0, 2);
	addGraphEdge(graph2, 1, 3);
	addGraphEdge(graph2, 2, 4);
	addGraphEdge(graph2, 3, 5);
	addGraphEdge(graph2, 4, 11);
	addGraphEdge(graph2, 5, 6);
	addGraphEdge(graph2, 5, 12);
	addGraphEdge(graph2, 6, 7);
	addGraphEdge(graph2, 7, 8);
	addGraphEdge(graph2, 8, 9);
	addGraphEdge(graph2, 9, 10);
	addGraphEdge(graph2, 10, 11);
	addGraphEdge(graph2, 11, 13);
	addGraphEdge(graph2, 12, 14);
	addGraphEdge(graph2, 13, 15);
	addGraphEdge(graph2, 14, 16);
	addGraphEdge(graph2, 15, 22);
	addGraphEdge(graph2, 16, 17);
	addGraphEdge(graph2, 16, 23);
	addGraphEdge(graph2, 17, 18);
	addGraphEdge(graph2, 18, 19);
	addGraphEdge(graph2, 19, 20);
	addGraphEdge(graph2, 20, 21);
	addGraphEdge(graph2, 21, 22);
	addGraphEdge(graph2, 22, 24);
	addGraphEdge(graph2, 23, 25);
	addGraphEdge(graph2, 24, 26);
	addGraphEdge(graph2, 25, 27);
	addGraphEdge(graph2, 26, 33);
	addGraphEdge(graph2, 27, 28);
	addGraphEdge(graph2, 27, 34);
	addGraphEdge(graph2, 28, 29);
	addGraphEdge(graph2, 29, 30);
	addGraphEdge(graph2, 30, 31);
	addGraphEdge(graph2, 31, 32);
	addGraphEdge(graph2, 32, 33);
	addGraphEdge(graph2, 33, 35);
	addGraphEdge(graph2, 34, 36);
	addGraphEdge(graph2, 35, 37);
	addGraphEdge(graph2, 36, 38);
	addGraphEdge(graph2, 37, 44);
	addGraphEdge(graph2, 38, 39);
	addGraphEdge(graph2, 39, 40);
	addGraphEdge(graph2, 40, 41);
	addGraphEdge(graph2, 41, 42);
	addGraphEdge(graph2, 42, 43);
	addGraphEdge(graph2, 43, 44);

	// Run chinese postman algorithm
	std::vector<unsigned int> node_traversal_2;
	node_traversal_2 = chinesePostman(graph2, 0);

	// Node traversal printed output
	printf("Node Traversal 2: ");
	for (index_traversal = 0; index_traversal < node_traversal_2.size(); index_traversal++) {
		printf("%d->", node_traversal_2[index_traversal]);
	}
	printf("DONE\n");

	return 0;
}
