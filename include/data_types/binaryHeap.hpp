#ifndef BINHEAP_H
#define BINHEAP_H


#include <iostream>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <list>


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

#endif

