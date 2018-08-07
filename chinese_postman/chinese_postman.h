#ifndef CHINESE_POSTMAN_H
#define CHINESE_POSTMAN_H

#include "../dijkstra/dijkstra.h"
#include <vector>
#include <limits.h>
#include <unordered_map>

std::vector<unsigned int> chinesePostman(std::vector<std::vector<unsigned int>> graph, unsigned int start_node);
std::vector<unsigned int> findOddNodes(std::vector<std::vector<unsigned int>> graph);
std::vector<std::vector<unsigned int>> findOddNodePairings(std::vector<unsigned int> odd_nodes, unsigned int start_index);
std::vector<unsigned int> bestOddPairingPath(std::vector<std::vector<unsigned int>> graph, std::vector<std::vector<unsigned int>> node_pairings);
std::vector<unsigned int> getEularianCircuit(std::vector<std::vector<unsigned int>> graph, unsigned int start_node);

#endif // CHINESE_POSTMAN_H
