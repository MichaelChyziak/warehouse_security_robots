#ifndef INTRUDER_H
#define INTRUDER_H

#include "../graph/graph.h"
#include "../warehouse/warehouse.h"
#include "../robots/robots.h"

const unsigned int vision = 5;
extern bool intruder_caught;

std::vector<std::vector<unsigned int>> intruderStart(unsigned int start_intruder_position, unsigned int current_index);
bool intruderValidMove(unsigned int move);
std::vector<std::vector<unsigned int>> intruderMovePatrol(unsigned int move, unsigned int current_index);
bool intruderFound(std::vector<std::vector<unsigned int>> updatedWarehosueLayout);
std::vector<std::vector<unsigned int>> intruderMoveChased(unsigned int move, std::vector<std::vector<unsigned int>> &old_graph);

#endif // INTRUDER_H