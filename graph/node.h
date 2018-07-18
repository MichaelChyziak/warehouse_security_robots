#ifndef NODE_H
#define NODE_H

#include <vector>
#include "edge.h"

class Node {
	public:
		Node(unsigned int id);
		unsigned int getId();
		void addEdge(Edge* edge);
		std::vector<Edge*> getEdges();
		unsigned int getNumEdges();
	private:
		unsigned int id;
		std::vector<Edge*> edges;
		unsigned int num_edges;
};

#endif // NODE_H
