#ifndef INTRUDER_H
#define INTRUDER_H

#include "../graph/graph.h"
#include "../warehouse/warehouse.h"

std::vector<std::vector<unsigned int>> intruderStart(unsigned int start_intruder_position, unsigned int current_index);
std::vector<std::vector<unsigned int>> intruderMove(unsigned int move);
bool intruderFound();

#endif // INTRUDER_H