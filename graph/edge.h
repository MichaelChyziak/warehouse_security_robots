#ifndef EDGE_H
#define EDGE_H

class Edge {
	public:
		Edge(unsigned int cost, unsigned int id);
		unsigned int getCost();
		unsigned int getId();
		void setUnhidden();
		void setHidden();
		bool getHidden();
	private:
		unsigned int cost;
		unsigned int id;
		bool hidden;
};

#endif // EDGE_H
