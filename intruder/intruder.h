#ifndef INTRUDER_H
#define INTRUDER_H

#include "../graph/graph.h"

std::vector<std::vector<unsigned int>> intruderStart(unsigned int start);
std::vector<std::vector<unsigned int>> intruderMove(unsigned int move);
bool intruderFound();

#endif // INTRUDER_H