#ifndef GREEDY_H
#define GREEDY_H


#include <vector>
#include <utility>
#include <iostream>
#include "Graph/graph.hpp"


std::vector<int>greedy(Graph G);

std::vector<int>smartGreedy(Graph G);

class BinaryHeap{
private:
	std::vector<std::pair<int, int>> heap;
	int numOfElements;
	int maxSize;
public:
	// Constructor
	BinaryHeap(int n);

	// Methods
	int parent(int i);
	int leftChild(int i);
	int rightChild(int i);
	void addElement(int label, int value);
	void pushDown(int pos);
	std::pair<int, int> getMax();
	void removeMax();
	int getNumberOfElements();
	void setMax(int label, int value);
	void printHeap();
};

std::vector<int>smarterGreedyHeap(Graph G);

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
	BucketsOfBuckets(Graph G);

	// Methods
	void printBucketsOfBuckets();
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

std::vector<int>smarterBucketsOfBuckets(Graph G);




#endif