#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "GraphBase.hpp"
#include "Edge.hpp"
#include "Vertex.hpp"
#include <iterator>
#include <queue>
#include <limits>
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_map>

class Graph : public GraphBase {
private:
	std::deque<Vertex*> vertices; 
	std::deque<Edge*> edges; 
	unsigned long shortest_distance = 0; 
	std::string minimum_element = "";
	int min_vertex_idx = 0; 
	std::priority_queue<std::pair<unsigned long, std::string>, std::vector<std::pair<unsigned long, std::string>>
    , std::greater<std::pair<unsigned long, std::string>>> pathQueue;

protected:
	
	void check_one_string(std::string input_string); 
	void check_two_string(std::string input_string1, std::string input_string2);
	void path_start(std::string startLabel); //Starts the path at A
	void make_path(std::string startLabel);//Make the path using the priority queue
	void find_min_vertex_idx(std::string& min_element); //Get the minimum index for a vertex
	void get_min_dist(std::string startLabel); //put distances in the string
	void traverse_path(std::string endLabel, std::vector<std::string>& path); // making a path
	void new_path(); //begin a new path

public:
	Graph() {} 
	~Graph(); 
	
	void addVertex(std::string label);
	void removeVertex(std::string label);
	void addEdge(std::string label1, std::string label2, unsigned long weight);
	void removeEdge(std::string label1, std::string label2);
	unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);

};
#endif