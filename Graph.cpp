#include "Graph.hpp"
// Destructor for the Graph class
Graph::~Graph() {
    for(auto& i : vertices) {delete i;}
    for(auto& j : edges) {delete j;}
    vertices.clear();
    edges.clear();
}

// Function to add a new vertex to the graph
void Graph::addVertex(std::string label){

    check_one_string(label);
    // Create a new vertex and initialize its attributes
    Vertex *new_vertex = new Vertex;
    new_vertex->vertex = label;
    new_vertex->minimum_distance = std::numeric_limits<unsigned long>::max();
    new_vertex->shortest_path = { "" };
    new_vertex->seen = false;
    vertices.push_back(new_vertex); // Add the new vertex to the vertices container

}

// Function to remove a vertex from the graph
void Graph::removeVertex(std::string label){

    check_one_string(label);    // Check that the input label is valid
    // Remove the vertex from the vertices container
    for (std::deque<Vertex*>::iterator vertex_it = vertices.begin(); vertex_it != vertices.end();) {
        if ((*vertex_it)->vertex == label) {
            vertices.erase(vertex_it);
        }
        ++vertex_it;
    }
    // Remove any edges connected to the removed vertex
    for (std::deque<Edge*>::iterator edge_it = edges.begin(); edge_it != edges.end();) {
        if (((*edge_it)->edge_a == label) || ((*edge_it)->edge_b == label)) {
            edges.erase(edge_it);
        }
        ++edge_it;
    }
}

// Function to add an edge to the graph
void Graph::addEdge(std::string label1, std::string label2, unsigned long weight){
    // Check that both input labels are valid
    check_two_string(label1, label2);

    // Create two new edges (one in each direction) with the given weight
    Edge *newedge1 = new Edge(label1, label2, weight);
    edges.push_back(newedge1);
    
    Edge *newedge2 = new Edge(label2, label1, weight);
    edges.push_back(newedge2);
}

//Function to remove an edge from the graph
void Graph::removeEdge(std::string label1, std::string label2){

    // Check that both input labels are valid
    check_two_string(label1, label2);

    // Loop through the edges in the graph
    for (std::deque<Edge*>::iterator edge_it = edges.begin(); edge_it != edges.end();) {
        // Check if the current edge matches the input labels
        if (((*edge_it)->edge_a == label1) && ((*edge_it)->edge_b == label2)) {
            // If there's a match, remove the edge from the list of edges
            edges.erase(edge_it);
        }
        ++edge_it;  // Move to the next edge in the container
    }
}

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path){

    check_two_string(startLabel, endLabel);
    //Select starting node
    path_start(startLabel); 
    //Makes the list in the priority queue in ascending order of nodes by their distances
    make_path(startLabel);
    //traverse priority queue and find the shortest distance from start to end
    traverse_path(endLabel, path); 
    //clears starting vertex
    new_path(); 

return shortest_distance;
}



void Graph::check_one_string(std::string input_string) {

    if(input_string.empty()) { //check if input string is empty
        throw("invalid string");    //if string is empty, throw exeception with message "invalid string"
    }
}

void Graph::check_two_string(std::string input_str1, std::string input_str2){

    if(input_str1.empty() || input_str2.empty()){   // Check if either of the input strings is empty
        throw("invalid string");    // If at least one of the strings is empty, throw an exception with the message "invalid string"
    }
}

void Graph::path_start(std::string startLabel){
    //loop through verticies i n the graph
    for (std::deque<Vertex*>::iterator ver_itr = vertices.begin(); ver_itr != vertices.end();) {
    // Check if the current vertex's label matches the provided startLabel    
    if ((*ver_itr)->vertex == startLabel) {
        // If there's a match, initialize the attributes for the start vertex
        (*ver_itr)->minimum_distance = 0;   // Set minimum distance to 0
        (*ver_itr)->shortest_path.clear();  // Clear the shortest_path vector
        (*ver_itr)->shortest_path.push_back(startLabel);    // Push the startLabel to the shortest_path

    }
    // If there's no match, do nothing for this vertex
    else{}
    // Move to the next vertex in the container
    ++ver_itr;
    }
    pathQueue.push(std::make_pair(0, startLabel));  // Push a pair (distance 0, startLabel) into the pathQueue to start the path finding
}

void Graph::find_min_vertex_idx(std::string& min_element){
    int ver_idx = 0;    //variable to keep track of the current vertex index

    //loop through the verticies in the graph
    for(std::deque<Vertex*>::iterator ver_itr = vertices.begin(); ver_itr != vertices.end();){
        if((*ver_itr)->vertex == min_element){  //check if current vertex label matches the min element
            min_vertex_idx = ver_idx;   //if theres a match set min_vertex_idx to current vertex index
        }
    else{
        ++ver_idx;  //if theres no match, increment vertex index
    }
    ++ver_itr; //move to the next vertex
    }
}

void Graph::get_min_dist(std::string startLabel){
    //outer loop iterates over edges. Looking at edges that originate from vertex with a label equal 
    //to minimum_element
    for (std::deque<Edge*>::iterator edge_itr = edges.begin(); edge_itr != edges.end();){
        if((*edge_itr) -> edge_a == minimum_element){
            //loop iterates over vertices looking at vertices that are adjacent to the current edge's destination 
            //vertex edge_b
            for (std::deque<Vertex*>::iterator ver_itr = vertices.begin(); ver_itr != vertices.end();){
                //checks: 1.if current edge connects to current vertex 2. if updating min distance 
                //through this edge results in smaller value than current min distance of vertex
                //3. whether vertex has been seen before
                if(((*edge_itr)->edge_b == (*ver_itr)->vertex && (vertices.at(min_vertex_idx)->minimum_distance + (*edge_itr)->weight) < (*ver_itr)->minimum_distance) 
                && ((*ver_itr)->seen == false)){
                    (*ver_itr)->minimum_distance = vertices.at(min_vertex_idx)->minimum_distance + (*edge_itr)->weight;
                    if(minimum_element == startLabel){
                        //clears the shortest_path vector associated with the current vertex pointed to by ver_itr
                        (*ver_itr)->shortest_path.clear(); 
                        (*ver_itr)->shortest_path.push_back(startLabel);
                    }
                    else if(minimum_element != startLabel){
                        (*ver_itr)->shortest_path.clear(); 
                        //copying the shortest path found so far to another vertex.
                        //extends the shortest path from the current vertex to include the min_vertex_idx vertex, 
                        //making it part of the shortest path
                        (*ver_itr)->shortest_path = vertices.at(min_vertex_idx)->shortest_path; 
                        (*ver_itr)->shortest_path.push_back(vertices.at(min_vertex_idx)->vertex); 
                    }
                //pair of min distance and vertex at the position of the iterator being pushed to priority queue    
                pathQueue.push(std::make_pair((*ver_itr)->minimum_distance, (*ver_itr)->vertex));
                }
                else{}
                ++ver_itr;
            }
        }
        else{}

        ++edge_itr;
    }
}

void Graph::make_path(std::string startLabel){

    for(;!pathQueue.empty();){  //loop runs until the queue is empty
        minimum_element = pathQueue.top().second;   //get vertex with the minimum distance from priority queue

        pathQueue.pop();    //remove the vertex from the priority queue

        find_min_vertex_idx(minimum_element);   //find the index of the vertex w/ the minimum distance
        get_min_dist(startLabel);   //calculate the minimum distance to the current vertex from the start vertex 

        vertices.at(min_vertex_idx)->seen = true;   //mark the current vertex as seen
    }
}

//This function resets the attributes of all vertices in the graph, preparing them 
//for a new path-finding or traversal operation
void Graph::new_path(){
    for(std::deque<Vertex*>::iterator ver_itr = vertices.begin(); ver_itr != vertices.end();){

        (*ver_itr)->minimum_distance = std::numeric_limits<unsigned long>::max();
        (*ver_itr)->shortest_path = { ""};
        (*ver_itr)->seen = false;

        ++ver_itr;
    }
}

void Graph::traverse_path(std::string endLabel, std::vector<std::string>& path){
    for (std::deque<Vertex*>::iterator vertex_it = vertices.begin(); vertex_it != vertices.end();) {
		if (endLabel == (*vertex_it)->vertex) { //Keep looping until the vertex iterator is at the end vertex
			shortest_distance = (*vertex_it)->minimum_distance; //Get the minimum distances and store them in the shortest_distance variable
			(*vertex_it)->shortest_path.push_back(endLabel); //Put the least weight in the string
			path = (*vertex_it)->shortest_path; //store that minimum path into vector of path and continue
		}
		else{}
		++vertex_it;
	}
}