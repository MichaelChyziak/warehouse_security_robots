#include "graph.h"

Graph::Graph() {
	num_nodes = 0;
	num_edges = 0;
}

Graph::Graph(unsigned int num_nodes) {
	unsigned int index;
	this->num_nodes = 0;
	for (index = 0; index < num_nodes; index++) {
		Node *new_node = new Node(num_nodes);
		nodes.push_back(new_node);
		this->num_nodes++;
	}
	num_edges = 0;
}

void Graph::addNode() {
	Node *new_node = new Node(num_nodes);
	nodes.push_back(new_node);
	num_nodes++;
}

void Graph::addEdge(Node *start, Node *end, unsigned int cost) {
	Edge *new_edge = new Edge(cost, num_edges);
	start->addEdge(new_edge);
	end->addEdge(new_edge);
	edges.push_back(new_edge);
	num_edges++;
}

std::vector<Node*> Graph::getNodes() {
	return nodes;
}

std::vector<Edge*> Graph::getEdges() {
	return edges;
}

unsigned int Graph::getNumNodes() {
	return num_nodes;
}

unsigned int Graph::getNumEdges() {
	return num_edges;
}
