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

std::vector<int>smarterBucketsOfBuckets(Graph G);




#endif