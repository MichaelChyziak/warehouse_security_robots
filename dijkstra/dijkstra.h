#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "../graph/graph.h"
#include <vector>
#include <limits.h>
#include <algorithm>

unsigned int dijkstraCost(std::vector<std::vector<unsigned int>> graph, unsigned int start, unsigned int destination);
std::vector<unsigned int> dijkstraVisitedNodes(std::vector<std::vector<unsigned int>> graph, unsigned int start, unsigned int destination);

#endif // DIJKSTRA_H
