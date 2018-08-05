#ifndef ROBOTS_H
#define ROBOTS_H

#include "../graph/graph.h"
#include "../dijkstra/dijkstra.h"
#include <vector>
#include <algorithm>

unsigned int findClosestRobotToIntruder(std::vector<std::vector<unsigned int>> graph, unsigned int intruder, unsigned int robot_1, unsigned int robot_2, unsigned int robot_3);
std::vector<unsigned int> followIntruder(std::vector<std::vector<unsigned int>> graph, unsigned int intruder, unsigned int robot);
std::vector<std::vector<unsigned int>> futureLocations(std::vector<std::vector<unsigned int>> graph, unsigned int start, unsigned int search_depth);
std::vector<std::vector<unsigned int>> futureLocationsOptimized(std::vector<std::vector<unsigned int>> graph, std::vector<std::vector<unsigned int>> future_locations);
std::vector<std::vector<float>> robotNodesScore(std::vector<std::vector<unsigned int>> graph, std::vector<std::vector<unsigned int>> robot_paths, std::vector<std::vector<unsigned int>> intruder_paths);
std::vector<std::pair<std::vector<unsigned int>, float>> robotPathsScore(std::vector<std::vector<unsigned int>> graph, std::vector<std::vector<unsigned int>> robot_paths, std::vector<std::vector<float>> robot_score);

#endif // ROBOTS_H