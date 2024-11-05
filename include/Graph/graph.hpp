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
    std::vector<std::vector<int>> adjMatrix;  // Adjacency matrix
    int numVertices;                          // Number of vertices
    std::vector<std::vector<int>> adjList;    // Adjacence 
    std::vector<int> selfLoops;               // List of vertices with self loops

public:
    // Constructor
    Graph(int vertices);
    // Read a graph from a PACE Challenge file 
    Graph(std::string filename);


    // Add an edge between vertex u and vertex v
    void addEdge(int u, int v);

    // Remove an edge between vertex u and vertex v
    //void removeEdge(int u, int v);

    // Delete all the edges with u as an endpoint
    void disconnectVertex(int u);

    // Check if an edge exists between vertex u and vertex v
    bool hasEdge(int u, int v);

    // Print the adjacency matrix
    void printGraph_console();

    // Get the number of vertices
    int vertexCount();

    // Clear the graph by resetting the adjacency matrix
    void clearGraph();

    // Getter 
    int getNumVertices();
    std::vector<int> getNeighbours(int v);
    std::vector<int> getSelfLoops();
};


#endif

