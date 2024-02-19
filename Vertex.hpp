#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <string>
#include <vector>

class Vertex{
private:
	std::string vertex; 
	unsigned long minimum_distance; 
	std::vector<std::string> shortest_path;
	bool seen; 

public:
	friend class Graph;
	
	Vertex() { vertex = ""; }
	~Vertex() {}
};
#endif