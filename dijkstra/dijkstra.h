#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "../graph/node.h"
#include "../graph/graph.h"
#include <limits.h>

unsigned int dijkstraCost(Graph *graph, Node* start, Node* destination);
unsigned int getNearestAdjacentNodeIndex(unsigned int optimal_distance[], bool node_included[], unsigned int num_nodes);

#endif // DIJKSTRA_H
