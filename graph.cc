#include "graph.h"

Graph::Graph() {
	num_nodes = 0;
	num_edges = 0;
}

void Graph::addNode() {
	Node new_node = new Node(num_of_nodes);
	nodes.push_back(new_node);
	num_nodes++;
}

void Graph::addEdge(Node node_a, Node node_b, unsigned int cost) {
	Edge new_edge = new Edge(node_a, node_b, cost, num_of_edges);
	edges.push_back(new_edge);
	num_edges++;
}

vector<Node> Graph::getNodes() {
	return nodes;
}

vector<Edge> Graph::getEdges() {
	return edges;
}

unsigned int Graph::getNumNodes() {
	return num_nodes;
}

unsigned int Graph::getNumEdges() {
	return num_edges;
}
