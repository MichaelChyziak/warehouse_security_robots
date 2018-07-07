#ifndef EDGE_H
#define EDGE_H

#include "node.h"

class Edge {
	public:
		Edge(Node node_a, Node node_b, unsigned int cost, unsigned int id);
		Node getNodeA();
		Node getNodeB();
		unsigned int getCost();
		unsigned int getId();
	private:
		Node node_a;
		Node node_b;
		unsigned int cost;
		unsigned int id;
};

#endif // EDGE_H
