#ifndef ROBOTS_H
#define ROBOTS_H

#include "../graph/graph.h"
#include "../dijkstra/dijkstra.h"
#include <vector>
#include <algorithm>

unsigned int findClosestRobotToIntruder(std::vector<std::vector<unsigned int>> graph, unsigned int intruder, unsigned int robot_1, unsigned int robot_2, unsigned int robot_3);
std::vector<unsigned int> followIntruder(std::vector<std::vector<unsigned int>> graph, unsigned int intruder, unsigned int robot);
std::vector<unsigned int> futureLocations(std::vector<std::vector<unsigned int>> graph, unsigned int start, unsigned int search_depth);
std::vector<unsigned int> futureLocationsOptimized(std::vector<std::vector<unsigned int>> graph, unsigned int start, std::vector<std::vector<unsigned int>> future_locations, unsigned int depth_search);
std::vector<std::vector<unsigned int>> futurePaths(std::vector<std::vector<unsigned int>> graph, unsigned int start, std::vector<unsigned int> future_locations);
std::vector<std::pair<std::vector<unsigned int>, unsigned int>> robotPathsScore(std::vector<std::vector<unsigned int>> graph, std::vector<std::vector<unsigned int>> robot_paths, std::vector<std::vector<unsigned int>> intruder_paths);
bool lowestScore(std::pair<std::vector<unsigned int>, unsigned int> first_pair, std::pair<std::vector<unsigned int>, unsigned int> second_pair);
bool isNonConflictingPath(std::vector<unsigned int> cutoff_path, std::vector<unsigned int> follow_path);
std::vector<std::vector<unsigned int>> controlRobots(std::vector<std::vector<unsigned int>> graph, unsigned int robot_1, unsigned int robot_2, unsigned int robot_3, unsigned int intruder, unsigned int search_depth);

#endif // ROBOTS_H