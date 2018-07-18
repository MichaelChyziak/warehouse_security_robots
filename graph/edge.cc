#include "edge.h"

Edge::Edge(unsigned int cost, unsigned int id) {
	this->cost = cost;
	this->id = id;
}

unsigned int Edge::getCost() {
	return cost;
}

unsigned int Edge::getId() {
	return id;
}
