#include "edge.h"

Edge::Edge(unsigned int cost, unsigned int id) {
	this->cost = cost;
	this->id = id;
	hidden = false;
}

unsigned int Edge::getCost() {
	return cost;
}

unsigned int Edge::getId() {
	return id;
}

void Edge::setUnhidden() {
	hidden = false;
}

void Edge::setHidden() {
	hidden = true;
}

bool Edge::getHidden() {
	return hidden;
}
