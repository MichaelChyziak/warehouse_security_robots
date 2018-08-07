#include <stdio.h>
#include "graph/graph.h"
#include "robots/robots.h"

int main(int argc, char* argv[]) {

	// DEMO (NODES EVERYWHERE AND EDGES ARE OF COST 1)
	// Create the following graph
	//       O       (0)
	//      O O	 	 (1, 2)
	//     O   O	 (3, 4)
	//    OOOOOOO    (5, 6, 7, 8, 9, 10, 11) --> Intruder at 11
	//    O     O	 (12, 13)
	//    O     O	 (14, 15)
	//    OOOOOOO    (16, 17, 18, 19, 20, 21, 22)
	//    O     O	 (23, 24)
	//    O     O	 (25, 26)
	//    OOOOOOO    (27, 28, 29, 30, 31, 32, 33)
	//    O     O	 (34, 35)
	//    O     O	 (36, 37)
	//    OOOOOOO    (38, 39, 40, 41, 42, 43, 44)
	std::vector<std::vector<unsigned int>> graph = createGraph(45);
	addGraphEdge(graph, 0, 1);
	addGraphEdge(graph, 0, 2);
	addGraphEdge(graph, 1, 3);
	addGraphEdge(graph, 2, 4);
	addGraphEdge(graph, 3, 5);
	addGraphEdge(graph, 4, 11);
	addGraphEdge(graph, 5, 6);
	addGraphEdge(graph, 5, 12);
	addGraphEdge(graph, 6, 7);
	addGraphEdge(graph, 7, 8);
	addGraphEdge(graph, 8, 9);
	addGraphEdge(graph, 9, 10);
	addGraphEdge(graph, 10, 11);
	addGraphEdge(graph, 11, 13);
	addGraphEdge(graph, 12, 14);
	addGraphEdge(graph, 13, 15);
	addGraphEdge(graph, 14, 16);
	addGraphEdge(graph, 15, 22);
	addGraphEdge(graph, 16, 17);
	addGraphEdge(graph, 16, 23);
	addGraphEdge(graph, 17, 18);
	addGraphEdge(graph, 18, 19);
	addGraphEdge(graph, 19, 20);
	addGraphEdge(graph, 20, 21);
	addGraphEdge(graph, 21, 22);
	addGraphEdge(graph, 22, 24);
	addGraphEdge(graph, 23, 25);
	addGraphEdge(graph, 24, 26);
	addGraphEdge(graph, 25, 27);
	addGraphEdge(graph, 26, 33);
	addGraphEdge(graph, 27, 28);
	addGraphEdge(graph, 27, 34);
	addGraphEdge(graph, 28, 29);
	addGraphEdge(graph, 29, 30);
	addGraphEdge(graph, 30, 31);
	addGraphEdge(graph, 31, 32);
	addGraphEdge(graph, 32, 33);
	addGraphEdge(graph, 33, 35);
	addGraphEdge(graph, 34, 36);
	addGraphEdge(graph, 35, 37);
	addGraphEdge(graph, 36, 38);
	addGraphEdge(graph, 37, 44);
	addGraphEdge(graph, 38, 39);
	addGraphEdge(graph, 39, 40);
	addGraphEdge(graph, 40, 41);
	addGraphEdge(graph, 41, 42);
	addGraphEdge(graph, 42, 43);
	addGraphEdge(graph, 43, 44);


	unsigned int search_depth = 10;
	unsigned int intruder = 11;
	unsigned int robot_1 = 43;
	unsigned int robot_2 = 44;
	unsigned int robot_3 = 38;
	std::vector<std::vector<unsigned int>> robot_paths;
	robot_paths = controlRobots(graph, robot_1, robot_2, robot_3, intruder, search_depth);

	for (int i = 0; i < robot_paths.size(); i++) {
		printf("Path %d:\n", i);
		for (int j = 0; j < robot_paths[i].size(); j++) {
			printf("%d->", robot_paths[i][j]);
		}
		printf("\n");
	}

	return 0;
}
