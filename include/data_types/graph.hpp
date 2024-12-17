#ifndef GRAPH_H
#define GRAPH_H


#include <iostream>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <list>
class Graph {
private:
    int numVertices;                          // Number of vertices
    int NumEdges;                             // Number of Edges
    std::vector<std::vector<int>> adjList;    // Adjacence 

public:
    // Constructor
    Graph(int vertices);
    Graph(const Graph& G);
    // Read a graph from a PACE Challenge file 
    Graph(std::string filename);


    // Add an edge between vertex u and vertex v
    void addEdge(int u, int v);


    // Delete all the edges with u as an endpoint
    void disconnectVertex(int u);

    // Print the adjacency matrix
    void printGraph_console() const;

    // Get the number of vertices
    int vertexCount()const;

    // Check if edge u v exists
    bool hasEdge(int u, int v)const;

    // Getter 
    int getNumVertices() const;
    std::vector<int> getNeighbours(int v) const;
    bool isIsolated(int v)const;
    int getDegree(int v)const;
};


#endif

