#ifndef EDGE_H
#define EDGE_H

class Edge {
	public:
		Edge(unsigned int cost, unsigned int id);
		unsigned int getCost();
		unsigned int getId();
	private:
		unsigned int cost;
		unsigned int id;
};

#endif // EDGE_H
