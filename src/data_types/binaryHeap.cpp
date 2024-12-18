#include "data_types/binaryHeap.hpp"


//////////////////////////////
//   Methods for Binary Heap
//////////////////////////////



// see https://www.geeksforgeeks.org/binary-heap/

BinaryHeap::BinaryHeap(int n){
	heap = {};
	for(int i = 0; i < n; i++){
		heap.push_back(std::pair<int , int>(-1, -1));
	}
	numOfElements = 0;
	maxSize = n;
};

int BinaryHeap::parent(int i){
	return (i - 1)/2;
}

int BinaryHeap::leftChild(int i){
	return 2*i + 1;
}

int BinaryHeap::rightChild(int i){
	return 2*i + 2;
}

void BinaryHeap::addElement(int label, int value){
	/*
	add an element to the heap
	*/
	std::pair<int, int> element(label, value);
	if(numOfElements == maxSize + 1){
		std::cout << "heap already full : " << numOfElements  << "/" << maxSize<< std::endl;
		exit ( EXIT_FAILURE );
	}
	// first, we put it at the end of the heap
	numOfElements++;
	int pos = numOfElements - 1;
	heap[pos] = std::pair<int, int>(label, value);

	// then we push it up 
	while(pos != 0 && heap[this->parent(pos)].second < heap[pos].second){
		std::pair<int, int> tmp = heap[pos];
		heap[pos] = heap[this->parent(pos)];
		heap[this->parent(pos)] = tmp;
	}
};


std::pair<int, int> BinaryHeap::getMax(){
	return heap[0];
};

void BinaryHeap::pushDown(int pos){
	/*
	We suppose that the subtree rooted at pos is correct except for pos
	correct the tree by pushing pos down
	*/
	int lc = this->leftChild(pos);
	int rc = this->rightChild(pos);
	int largets = pos;
	if(lc < numOfElements && heap[lc].second > heap[pos].second){
		largets = lc;
	}
	if(rc < numOfElements && heap[rc].second > heap[pos].second){
		largets = rc;
	}
	if(largets != pos){
		std::pair<int, int> tmp = heap[largets];
		heap[largets] = heap[pos];
		heap[pos] = tmp;
		this->pushDown(largets);
	}
	return;
};


void BinaryHeap::removeMax(){
	if(numOfElements <= 0){
		std::cout << "heap already empty" << std::endl;
		exit ( EXIT_FAILURE );
	}
	if(numOfElements == 1){
		numOfElements--;
	}
	else{
		numOfElements--;
		std::pair<int, int> tmp = heap[numOfElements];
		heap[numOfElements] = heap[0];
		heap[0] = tmp;
		this->pushDown(0);
	}
};

int BinaryHeap::getNumberOfElements(){
	return numOfElements;
}

void BinaryHeap::setMax(int label, int value){
	heap[0] = std::pair<int, int>(label, value);
}

void BinaryHeap::printHeap(){
	std::cout << numOfElements << "/" << maxSize << " elements\n";
	for(int i = 0; i < numOfElements; i++){
		std::cout << heap[i].first << " ";
	}
	std::cout << " // ";
	for(int i = numOfElements; i < maxSize; i++){
		std::cout << heap[i].first << " ";
	}
	std::cout << std::endl;
}
