#ifndef CHINESE_POSTMAN_H
#define CHINESE_POSTMAN_H

#include "../graph/graph.h"
#include "../dijkstra/dijkstra.h"
#include <vector>
#include <limits.h>
#include <utility>

std::vector<Node*> chinesePostman(Graph *graph, Node* start_node);
std::vector<Node*> findOddNodes(std::vector<Node*> nodes, unsigned int num_nodes);
std::vector<std::vector<Node*>> findOddNodePairings(std::vector<Node*> odd_nodes, unsigned int start_index);
std::vector<Node*> bestOddPairingPath(Graph *graph, std::vector<std::vector<Node*>> node_pairings);
std::vector<Node*> getEularianCircuit(Graph* graph, Node* start_node);

#endif // CHINESE_POSTMAN_H
