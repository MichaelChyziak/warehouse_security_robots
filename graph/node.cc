#include "node.h"

Node::Node(unsigned int id) {
	this->id = id;
	num_edges = 0;
	num_neighbours = 0;
}

unsigned int Node::getId() {
	return id;
}

void Node::addEdge(Edge* edge, Node* neighbour) {
	
	// Variables
	unsigned int index_neighbours;
	bool new_neighbour = true;

	edges.push_back(edge);
	num_edges++;
	
	neighbour->edges.push_back(edge);
	neighbour->num_edges++;

	for (index_neighbours = 0; index_neighbours < num_neighbours; index_neighbours++) {
		if (neighbours[index_neighbours] == neighbour) {
			new_neighbour = false;
			break;
		}
	}
	if (new_neighbour == true) {
		neighbours.push_back(neighbour);
		num_neighbours++;

		neighbour->neighbours.push_back(this);
		neighbour->num_neighbours++;
	}
}

std::vector<Edge*> Node::getSharedEdges(Node* neighbour) {
	
	// Variables
	unsigned int index_neighbour;
	unsigned int index_edges;
	unsigned int index_edges_neighbours;
	std::vector<Edge*> shared_edges;

	for (index_neighbour = 0; index_neighbour < num_neighbours; index_neighbour++) {
		for (index_edges = 0; index_edges < num_edges; index_edges++) {
			for (index_edges_neighbours = 0; index_edges_neighbours < neighbour->getNumEdges(); index_edges_neighbours++) {
				if (neighbours[index_neighbour]->getEdges()[index_edges_neighbours] == edges[index_edges]) {
					shared_edges.push_back(edges[index_edges]);
				}
			}
		}
	}

	return shared_edges;
}

// Will return the lowest edge cost between self and neighbour
// Edge must be confirmed to exist
// neighbour node must be a valid neighbour node
unsigned int Node::sharedEdgeMinCost(Node *neighbour) {
	
	// Variables
	unsigned int edge_min_cost = INT_MAX;
	unsigned int edge_index;
	std::vector<Edge*> shared_edges;
	shared_edges = getSharedEdges(neighbour);

	for (edge_index = 0; edge_index < shared_edges.size(); edge_index++) {
		if (shared_edges[edge_index]->getCost() < edge_min_cost) {
			edge_min_cost = shared_edges[edge_index]->getCost();
		}
	}

	return edge_min_cost;
}

std::vector<Node*> Node::getNeighbours() {
	return neighbours;
}

std::vector<Edge*> Node::getEdges() {
	return edges;
}

unsigned int Node::getNumEdges() {
	return num_edges;
}

unsigned int Node::getNumNeighbours() {
	return num_neighbours;
}

bool Node::hasUnhiddenEdge() {

	// Variables
	unsigned int index_edge;

	for (index_edge = 0; index_edge < num_edges; index_edge++) {
		// If false means that values edges are unhidden
		if (edges[index_edge]->getHidden() == false) {
			return true;
		}
	}

	return false;
}

std::vector<Edge*> Node::getUnhiddenEdges() {
	
	// Variables
	unsigned int index_edge;
	std::vector<Edge*> unhidden_edges;

	for (index_edge = 0; index_edge < num_edges; index_edge++) {
		if (edges[index_edge]->getHidden() == false) {
			unhidden_edges.push_back(edges[index_edge]);
		}
	}

	return unhidden_edges;
}

// Must provide an valid edge that is shared with this node
Node* Node::getNeighbour(Edge* shared_edge) {

	// Variables
	unsigned int index_neighbours;

	for (index_neighbours = 0; index_neighbours < num_neighbours; index_neighbours++) {
		if (neighbours[index_neighbours]->hasEdge(shared_edge) == true) {
			return neighbours[index_neighbours];
		}
	}



}

bool Node::hasEdge(Edge* edge) {
	
	// Variables
	unsigned int index_edges;

	for (index_edges = 0; index_edges < num_edges; index_edges++) {
		if (edges[index_edges] == edge) {
			return true;
		}
	}

	return false;
}
