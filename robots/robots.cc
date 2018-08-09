#include "robots.h"
// #include <time.h> // TODO remove
// #include <stdio.h> // TODO REMOVE
// Returns robot closest to intruder
// Intruder and robot_x are their location
unsigned int findClosestRobotToIntruder(std::vector<std::vector<unsigned int>> &graph, unsigned int intruder, unsigned int robot_1, unsigned int robot_2, unsigned int robot_3) {
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
std::vector<unsigned int> followIntruder(std::vector<std::vector<unsigned int>> &graph, unsigned int intruder, unsigned int robot) {
	std::vector<unsigned int> robot_path = dijkstraVisitedNodes(graph, robot, intruder);
	return robot_path;
}

// Finds all of the possible future locations with the search depth
// Currently assumes non-rational moves
std::vector<unsigned int> futureLocations(std::vector<std::vector<unsigned int>> graph, unsigned int start, unsigned int search_depth) {
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

	return locations[depth_index - 1];
}

// Optimizes so that only locations with dijkstra from origin = depth are shown
std::vector<unsigned int> futureLocationsOptimized(std::vector<std::vector<unsigned int>> graph, unsigned int start, std::vector<unsigned int> future_locations, unsigned int depth_search) {
	unsigned int nodes_index;
	unsigned int cost;
	std::vector<unsigned int> locations_optimized;

	for (nodes_index = 0; nodes_index < future_locations.size(); nodes_index++) {
		cost = dijkstraCost(graph, start, future_locations[nodes_index]);
		if (cost == depth_search) {
			locations_optimized.push_back(future_locations[nodes_index]);
		}
	}

	return locations_optimized;
}

// Gets all paths from start to future locations
std::vector<std::vector<unsigned int>> futurePaths(std::vector<std::vector<unsigned int>> graph, unsigned int start, std::vector<unsigned int> future_locations) {
	unsigned int paths_index;
	std::vector<unsigned int> path;
	std::vector<std::vector<unsigned int>> future_paths;

	for (paths_index = 0; paths_index < future_locations.size(); paths_index++) {
		path = dijkstraVisitedNodes(graph, start, future_locations[paths_index]);
		future_paths.push_back(path);
	}

	return future_paths;
}

// Returns each possible path to the full depth and returns the total score
// First element of pair is the path traversed, second element is the score of the path
// The lower the score the better
std::vector<std::pair<std::vector<unsigned int>, unsigned int>> robotPathsScore(std::vector<std::vector<unsigned int>> &graph, std::vector<std::vector<unsigned int>> robot_paths, std::vector<std::vector<unsigned int>> intruder_paths) {

	// Variables
	unsigned int robot_paths_index;
	unsigned int intruder_paths_index;
	unsigned int path_index;
	unsigned int score;
	std::pair<std::vector<unsigned int>, unsigned int> path_score_pair;
	std::vector<std::pair<std::vector<unsigned int>, unsigned int>> path_score_pairs;

	for (robot_paths_index = 0; robot_paths_index < robot_paths.size(); robot_paths_index++) {
		score = 0;
		for (intruder_paths_index = 0; intruder_paths_index < intruder_paths.size(); intruder_paths_index++) {
			for (path_index = 0; path_index < robot_paths[robot_paths_index].size() && path_index < intruder_paths[intruder_paths_index].size(); path_index++) {
				// In this scenario we "catch" the intruder (intruder moves first and then we move, but calculate simultaneously as if moving at "same" time)
				if (intruder_paths[intruder_paths_index][path_index] == robot_paths[robot_paths_index][path_index] || (path_index > 0 && intruder_paths[intruder_paths_index][path_index] == robot_paths[robot_paths_index][path_index - 1])) {
					break; // Best case scenario, don't add to score. Move onto next intruder path
				}
				// Get the final score since we don't "catch" intruder
				if (path_index == robot_paths[robot_paths_index].size() - 1 || path_index == intruder_paths[intruder_paths_index].size() -1) {
					// TODO TESTING
			 		score += dijkstraCost(graph, robot_paths[robot_paths_index][path_index], intruder_paths[intruder_paths_index][path_index]);
			 		// score += manhattanDistance(robot_paths[robot_paths_index][path_index], intruder_paths[intruder_paths_index][path_index]);
				}
			}
		}
		path_score_pair = std::make_pair(robot_paths[robot_paths_index], score);
		path_score_pairs.push_back(path_score_pair);
	}

	return path_score_pairs;
}

// Return if first_pair score is less than second_pair score
bool lowestScore(std::pair<std::vector<unsigned int>, unsigned int> first_pair, std::pair<std::vector<unsigned int>, unsigned int> second_pair) {
	bool lower_score_bool;

	if (first_pair.second < second_pair.second) {
		lower_score_bool = true;
	}
	else {
		lower_score_bool = false;
	}

	return lower_score_bool;
}

// Returns true if the two paths do not conflict or overlap, false otherwise
bool isNonConflictingPath(std::vector<unsigned int> cutoff_path, std::vector<unsigned int> follow_path) {
	unsigned int follow_path_index;
	unsigned int cutoff_path_index;

	// False if final destination is the same, conflicting
	if (cutoff_path[cutoff_path.size() - 1] == follow_path[follow_path.size() -1]) {
		return false;
	}

	// False if the last 2 cutoff nodes repeats any of the follow paths nodes (in a row)
	for (follow_path_index = 0; follow_path_index + 1 < follow_path.size(); follow_path_index++) {
		if (cutoff_path[cutoff_path.size() - 2] == follow_path[follow_path_index] && cutoff_path[cutoff_path.size() - 1] == follow_path[follow_path_index + 1]) {
			return false;
		}
	}

	// TODO UNSURE ABOUT THIS AND IF IT SHOULD BE INCLUDED OR A VARIATION OF IT???
	// If they criss-cross each other (one goes: 1->2, other goes 2->1) anywhere in their paths
	for (follow_path_index = 0; follow_path_index + 1 < follow_path.size(); follow_path_index++) {
		for (cutoff_path_index = 1; cutoff_path_index < cutoff_path.size(); cutoff_path_index++) {
			if (follow_path[follow_path_index] == cutoff_path[cutoff_path_index] && follow_path[follow_path_index + 1] == cutoff_path[cutoff_path_index - 1]) {
				return false;
			}
		}
	}
	
	return true;
}

// Returns the path that robots follow, cutoff 1, and cutoff 2 should take (in that order)
std::vector<std::vector<unsigned int>> controlRobots(std::vector<std::vector<unsigned int>> graph, unsigned int robot_1, unsigned int robot_2, unsigned int robot_3, unsigned int intruder, unsigned int search_depth) {
// clock_t start = clock();
// clock_t stop;
	// Variables
	unsigned int robot_closest;
	std::vector<unsigned int> follow_path;
	std::vector<unsigned int> intruder_locations;
	std::vector<std::vector<unsigned int>> intruder_paths;
	unsigned int robot_cutoff_1;
	std::vector<unsigned int> cutoff_locations_1;
	std::vector<std::vector<unsigned int>> cutoff_paths_1;
	std::vector<std::pair<std::vector<unsigned int>, unsigned int>> path_score_pairs_1;
	unsigned int robot_cutoff_2;
	std::vector<unsigned int> cutoff_locations_2;
	std::vector<std::vector<unsigned int>> cutoff_paths_2;
	std::vector<std::pair<std::vector<unsigned int>, unsigned int>> path_score_pairs_2;
	std::vector<std::pair<std::vector<unsigned int>, unsigned int>> path_score_pairs;
	unsigned int cutoff_index;
	std::vector<unsigned int> cutoff_1_path;
	std::vector<unsigned int> cutoff_2_path;
	std::vector<std::vector<unsigned int>> final_paths;

	// Closest robot
	robot_closest = findClosestRobotToIntruder(graph, intruder, robot_1, robot_2, robot_3);
	follow_path = followIntruder(graph, intruder, robot_closest);

	// Intruder locations
	intruder_locations = futureLocations(graph, intruder, search_depth);
	intruder_locations = futureLocationsOptimized(graph, intruder, intruder_locations, search_depth);
	intruder_paths = futurePaths(graph, intruder, intruder_locations);

	// Cutoff robot 1 score
	if (robot_closest == robot_1) {
		robot_cutoff_1 = robot_2;
	}
	else {
		robot_cutoff_1 = robot_1;
	}
	cutoff_locations_1 = futureLocations(graph, robot_cutoff_1, search_depth);
	cutoff_locations_1 = futureLocationsOptimized(graph, robot_cutoff_1, cutoff_locations_1, search_depth);
	cutoff_paths_1 = futurePaths(graph, robot_cutoff_1, cutoff_locations_1);
	path_score_pairs_1 = robotPathsScore(graph, cutoff_paths_1, intruder_paths);

	// Cutoff robot score 2
	if (robot_closest == robot_1) {
		if (robot_cutoff_1 == robot_2) {
			robot_cutoff_2 = robot_3;
		}
		else {
			robot_cutoff_2 = robot_2;
		}
	}
	else {
		if (robot_cutoff_1 == robot_1) {
			robot_cutoff_2 = robot_3;
		}
		else {
			robot_cutoff_2 = robot_1;
		}
	}

	cutoff_locations_2 = futureLocations(graph, robot_cutoff_2, search_depth);
	cutoff_locations_2 = futureLocationsOptimized(graph, robot_cutoff_2, cutoff_locations_2, search_depth);
	cutoff_paths_2 = futurePaths(graph, robot_cutoff_2, cutoff_locations_2);
	path_score_pairs_2 = robotPathsScore(graph, cutoff_paths_2, intruder_paths);

	// Combine both cutoff paths into one large path list
	// Sorts the path score pairs from best to worst (lowest to height score)
	path_score_pairs.reserve(path_score_pairs_1.size() + path_score_pairs_2.size() ); // preallocate memory
	path_score_pairs.insert(path_score_pairs.end(), path_score_pairs_1.begin(), path_score_pairs_1.end() );
	path_score_pairs.insert(path_score_pairs.end(), path_score_pairs_2.begin(), path_score_pairs_2.end() );
	std::sort(path_score_pairs.begin(), path_score_pairs.end(), lowestScore);

	// Find best lowest score from both cutoff robots and see if that overlaps/conflicts with the follow robot, if not pick that
	for (cutoff_index = 0; cutoff_index < path_score_pairs.size(); cutoff_index++) {
		if (isNonConflictingPath(path_score_pairs[cutoff_index].first, follow_path) == true) {
			if (cutoff_1_path.empty() == true) {
				cutoff_1_path = path_score_pairs[cutoff_index].first;
				// Remove already chosen path (if there is another path possible)
				if (path_score_pairs.size() > 1) {
					path_score_pairs.erase(path_score_pairs.begin() + cutoff_index);
				}
			}
			// If starting locations are same as cutoff_1_path, cannot take (since that is for a different robot)
			else if (path_score_pairs[cutoff_index].first[0] != cutoff_1_path[0] && isNonConflictingPath(path_score_pairs[cutoff_index].first, cutoff_1_path) == true) {
				cutoff_2_path = path_score_pairs[cutoff_index].first;
				break;
			}
		}
	}

	// When both (or just one) cutoff paths have not been chosen yet
	if (cutoff_2_path.empty() == true) {
		if (cutoff_1_path.empty() == true) {
			cutoff_1_path = path_score_pairs[0].first;
			// Remove already chosen path (if there is another path possible)
			if (path_score_pairs.size() > 1) {
				path_score_pairs.erase(path_score_pairs.begin() + cutoff_index);
			}
		}
		for (cutoff_index = 1; cutoff_index < path_score_pairs.size(); cutoff_index++) {
			// If starting locations are same as cutoff_1_path, cannot take (since that is for a different robot)
			if (path_score_pairs[cutoff_index].first[0] != cutoff_1_path[0]) {
				cutoff_2_path = path_score_pairs[cutoff_index].first;
			}
		}
	}

	// If cutoff_2_path still not chosen, take the first best remaining path regardless
	if (cutoff_2_path.empty() == true) {
		cutoff_2_path = path_score_pairs[0].first;
	}
// stop = clock();
// printf ("time: %f seconds.\n",((float)stop-start)/CLOCKS_PER_SEC);
	// Add all best paths here in order: follow, cutoff 1, cutoff 2
	final_paths.push_back(follow_path);
	final_paths.push_back(cutoff_1_path);
	final_paths.push_back(cutoff_2_path);
	return final_paths;
}

// Used as heuristic for quicker dijkstras
unsigned int manhattanDistance(unsigned int node_current, unsigned int node_destination) {
	std::pair<unsigned int, unsigned int> node_current_position;
	std::pair<unsigned int, unsigned int> node_destination_position;

	node_current_position = getNodeCoordinate(warehouse_big, node_current);
	node_destination_position = getNodeCoordinate(warehouse_big, node_destination);

	return (abs(node_current_position.first - node_destination_position.first) + abs(node_current_position.second - node_destination_position.second));
}
