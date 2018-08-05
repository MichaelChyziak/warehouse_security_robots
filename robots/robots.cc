#include "robots.h"

// Returns robot closest to intruder
// Intruder and robot_x are their location
unsigned int findClosestRobotToIntruder(std::vector<std::vector<unsigned int>> graph, unsigned int intruder, unsigned int robot_1, unsigned int robot_2, unsigned int robot_3) {
	unsigned int robot_1_cost;
	unsigned int robot_2_cost;
	unsigned int robot_3_cost;
	robot_1_cost = dijkstraCost(graph, robot_1, intruder);
	robot_2_cost = dijkstraCost(graph, robot_2, intruder);
	robot_3_cost = dijkstraCost(graph, robot_3, intruder);
	if (robot_1_cost < robot_2_cost) {
		if (robot_1_cost < robot_3_cost) {
			return robot_1;
		}
		else {
			return robot_3;
		}
	}
	else {
		if (robot_2_cost < robot_3_cost) {
			return robot_2;
		}
		else {
			return robot_3;
		}
	}
}

// Returns path the robot should go to to follow the intruder
// Output is given in reverse order
std::vector<unsigned int> followIntruder(std::vector<std::vector<unsigned int>> graph, unsigned int intruder, unsigned int robot) {
	std::vector<unsigned int> robot_path = dijkstraVisitedNodes(graph, robot, intruder);
	return robot_path;
}

std::vector<std::vector<unsigned int>> futureLocations(std::vector<std::vector<unsigned int>> graph, unsigned int start, unsigned int search_depth) {
	unsigned int depth_index;
	unsigned int index;
	unsigned int neighbours_index;
	std::vector<std::vector<unsigned int>> locations;
	std::vector<unsigned int> intermediate_locations;
	std::vector<unsigned int> intermediate_neighbours;
	
	// Initialize
	intermediate_locations.push_back(start);
	locations.push_back(intermediate_locations);

	// Run algorithm
	for (depth_index = 1; depth_index <= search_depth; depth_index++) {
		intermediate_locations.clear();
		for (index = 0; index < locations[depth_index - 1].size(); index++) {
			intermediate_neighbours = getGraphNodeNieghbours(graph, locations[depth_index - 1][index]);
			for (neighbours_index = 0; neighbours_index < intermediate_neighbours.size(); neighbours_index++) {
				// Removes multiples
				if ((std::find(intermediate_locations.begin(), intermediate_locations.end(), intermediate_neighbours[neighbours_index]) != intermediate_locations.end()) == false) {
					intermediate_locations.push_back(intermediate_neighbours[neighbours_index]);
				}
			}
		}
		locations.push_back(intermediate_locations);
	}

	return locations;
}

// Optimizes so that only locations with dijkstra from origin = depth are shown
std::vector<std::vector<unsigned int>> futureLocationsOptimized(std::vector<std::vector<unsigned int>> graph, std::vector<std::vector<unsigned int>> future_locations) {
	unsigned int depth_index;
	unsigned int nodes_index;
	unsigned int cost;
	std::vector<std::vector<unsigned int>> locations_optimized;
	std::vector<unsigned int> locations_intermediate_optimized;

	for (depth_index = 0; depth_index < future_locations.size(); depth_index++) {
		locations_intermediate_optimized.clear();
		for (nodes_index = 0; nodes_index < future_locations[depth_index].size(); nodes_index++) {
			cost = dijkstraCost(graph, future_locations[0][0], future_locations[depth_index][nodes_index]);
			if (cost == depth_index) {
				locations_intermediate_optimized.push_back(future_locations[depth_index][nodes_index]);
			}
		}
		locations_optimized.push_back(locations_intermediate_optimized);
	}

	return locations_optimized;
}

// Stores a one-one corresponding "score" to each possible destination in robot_paths (0 = the worst, higher numbers = better)
std::vector<std::vector<unsigned int>> getRankedRobotPaths(std::vector<std::vector<unsigned int>> graph, std::vector<std::vector<unsigned int>> robot_paths, std::vector<std::vector<unsigned int>> intruder_paths) {
	unsigned int paths_index;
	unsigned int nodes_robot_index;
	unsigned int nodes_intruder_index;
	unsigned int score;
	std::vector<std::vector<unsigned int>> scores;
	std::vector<unsigned int> intermediate_scores;

	// First one in robot_paths is our current location, staying in spot is not an option (for now)
	// Therefore gets worst score possible, 0
	intermediate_scores.push_back(0);
	scores.push_back(intermediate_scores);

	for (paths_index = 0; paths_index + 1 < robot_paths.size() && paths_index < intruder_paths.size(); paths_index++) {
		intermediate_scores.clear();
		for (nodes_robot_index = 0; nodes_robot_index < robot_paths[paths_index + 1].size(); nodes_robot_index++) {
			score = 0;
			for (nodes_intruder_index = 0; nodes_intruder_index < intruder_paths[paths_index].size(); nodes_intruder_index++) {
				if (robot_paths[paths_index + 1][nodes_robot_index] == intruder_paths[paths_index][nodes_intruder_index]) {
					score += 1;
				}
			}
			intermediate_scores.push_back(score);
		}
		scores.push_back(intermediate_scores);
	}

	return scores;
}