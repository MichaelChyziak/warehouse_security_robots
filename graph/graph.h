#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "node.h"
#include "edge.h"

class Graph {
	public:
		Graph();
		Graph(unsigned int num_nodes);
		void addNode();
		void addEdge(Node *start, Node *end, unsigned int cost);
		std::vector<Node*> getNodes();
		std::vector<Edge*> getEdges();
		unsigned int getNumNodes();
		unsigned int getNumEdges();
	private:
		std::vector<Node*> nodes;
		std::vector<Edge*> edges;
		unsigned int num_nodes;
		unsigned int num_edges;
};

#endif // GRAPH_H
