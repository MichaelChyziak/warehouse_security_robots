#ifndef CHINESE_POSTMAN_H
#define CHINESE_POSTMAN_H

#include "../graph/graph.h"
#include "../dijkstra/dijkstra.h"
#include <vector>
#include <limits.h>

void chinesePostman(Graph *graph);
std::vector<Node*> findOddNodes(std::vector<Node*> nodes, unsigned int num_nodes);
std::vector<std::vector<Node*>> findOddNodePairings(std::vector<Node*> odd_nodes, unsigned int start_index);
std::vector<Node*> bestOddPairingPath(Graph *graph, std::vector<std::vector<Node*>> node_pairings);

#endif // CHINESE_POSTMAN_H
