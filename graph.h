#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "node.h"
#include "edge.h"

class Graph {
	public:
		Graph();
		void addNode();
		void addEdge(Node node_a, Node node_b, unsigned int cost);
		vector<Node> getNodes();
		vector<Edge> getEdges();
		unsigned int getNumNodes();
		unsigned int getNumEdges();
	private:
		vector<Node> nodes;
		vector<Edge> edges;
		unsigned int num_nodes;
		unsigned int num_edges;
};

#endif // GRAPH_H
