#ifndef NODE_H
#define NODE_H

#include <vector>
#include "edge.h"
#include <limits.h>

class Node {
	public:
		Node(unsigned int id);
		unsigned int getId();
		void addEdge(Edge* edge, Node* neighbour);
		std::vector<Edge*> getSharedEdges(Node* neighbour);
		unsigned int sharedEdgeMinCost(Node *neighbour);
		std::vector<Node*> getNeighbours();
		std::vector<Edge*> getEdges();
		unsigned int getNumEdges();
		unsigned int getNumNeighbours();
	private:
		unsigned int id;
		std::vector<Edge*> edges;
		std::vector<Node*> neighbours;
		unsigned int num_edges;
		unsigned int num_neighbours;
};

#endif // NODE_H
