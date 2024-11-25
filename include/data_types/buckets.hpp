#ifndef BUCKET_H
#define BUCKET_H


#include <iostream>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include "data_types/graph.hpp"

class BucketsOfBuckets{
private:
	int maxDegree;
	int numOfElements;
	int head;
	std::vector<int> heads;
	std::vector<int> pred_bucket;
	std::vector<int> next_bucket;
	std::vector<int> pred_vertex;
	std::vector<int> next_vertex;
	std::vector<int> currentDegree;
public:
	// Constructor
	BucketsOfBuckets(Graph *G);

	// Methods
	void printBucketsOfBuckets();
	void printBucketsOfBucketsV2();
	void remove_bucket(int d);
	void remove_vertex_from_bucket(int v, int d);
	void pushVertexUp(int v, int d);
	void decreaseVertex(int v);
	void deleteVertex(int v);


	// Getters and Setters
	int getNumberOfElements();
	int getMaxDegree();
	int getHead();
	int getHeadVertex();
};


#endif

