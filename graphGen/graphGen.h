#ifndef GRAPHGEN_H
#define GRAPHGEN_H

#include <vector>
#include <iostream>
#include <algorithm>

#include "../graph/graph.h"

const unsigned int PATH     = 0;
const unsigned int WALL     = 1;
const unsigned int DOOR     = 2;
const unsigned int OBSTACLE = 3;

std::vector< std::vector<unsigned int> > createWarehouseGraph(std::vector< std::vector<unsigned int> > warehouse);

#endif