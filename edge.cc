#include "edge.h"

Edge::Edge(Node node_a, Node node_b, unsigned int cost, unsigned int id) {
	this->node_a = node_a;
	this->node_b = node_b;
	this->cost = cost;
	this->id = id;
}

Node Edge::getNodeA() {
	return node_a;
}

Node Edge::getNodeB() {
	return node_b;
}

unsigned int Edge::getCost() {
	return cost;
}

unsigned int Edge::getId() {
	return id;
}
