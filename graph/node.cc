#include "node.h"

Node::Node(unsigned int id) {
	this->id = id;
}

unsigned int Node::getId() {
	return id;
}

void Node::addEdge(Edge* edge) {
	edges.push_back(edge);
	num_edges++;
}

std::vector<Edge*> Node::getEdges() {
	return edges;
}

unsigned int Node::getNumEdges() {
	return num_edges;
}
