#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "../graph/node.h"
#include "../graph/graph.h"
#include <limits.h>
#include <utility>

unsigned int dijkstraCost(Graph *graph, Node* start, Node* destination);
std::pair<std::vector<Node*>, std::vector<unsigned int>> dijkstraVisitedNodes(Graph *graph, Node* start, Node* destination);

#endif // DIJKSTRA_H
