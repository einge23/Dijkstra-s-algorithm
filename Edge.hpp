#ifndef EDGE_HPP
#define EDGE_HPP

#include <string>

class Edge {
private:
	std::string edge_a; 
	std::string edge_b; 
	unsigned long weight; 

public:
	friend class Graph;

	Edge(std::string a = "", std::string b = "", unsigned long w = 0) {
		edge_a = a;
		edge_b = b;
		weight = w;
	}
	~Edge() {}
};
#endif 