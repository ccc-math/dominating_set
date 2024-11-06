
#include "Algo/greedy.hpp"





std::vector<int> greedy(Graph G){
	std::vector<int> dom = {};
	std::vector<bool> isDom = {};
	int n = G.getNumVertices();
	for(int i = 0; i < n; i++){
		isDom.push_back(false);
	}
	for(int i = 0; i < n; i++){
		if(!isDom[i]){
			dom.push_back(i);
			isDom[i] = true;
			for(int u : G.getNeighbours(i)){
				isDom[u] = true;
			}
		}
	}
	return dom;
}


std::vector<int> smartGreedy(Graph G){
	int n = G.getNumVertices();
	std::vector<bool>dom(n, false);
	std::vector<bool>isDom(n, false);
	for(int i = 0; i < n; i++){
		if(G.isIsolated(i)){
			dom[i] = true;
		}
	}

	bool flag = true;
	while(flag){
		flag = false;
		int maxDeg = -1;
		int maxDegVertex = -1;
		// We look for the vertex of max degree
		for(int i = 0; i < n; i++){
			if(!isDom[i] && G.getDegree(i) > maxDeg){
				maxDeg = G.getDegree(i);
				maxDegVertex = i;
				flag = true;
			}
		}
		if(flag){
			dom[maxDegVertex] = true;
			isDom[maxDegVertex] = true;
			for(int u : G.getNeighbours(maxDegVertex)){
				isDom[u] = true;
				G.disconnectVertex(u);
			}
			G.disconnectVertex(maxDegVertex);
		}
	}
	std::vector<int> res = {};
	for(int i = 0; i < n; i++){
		if(dom[i]){
			res.push_back(i);
		}
	}
	return res;
}

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
	std::cout << std::endl;
	for(int i = numOfElements; i < maxSize; i++){
		std::cout << heap[i].first << " ";
	}
	std::cout << std::endl;
}


//////////////////////////////
//   Smart Greedy with Heap
//////////////////////////////

std::vector<int> smarterGreedyHeap(Graph G){
	int n = G.getNumVertices();
	std::vector<bool> isDom(n, false);
	std::vector<int> dom = {};
	std::vector<int> degreeInG(n, 0);
	BinaryHeap heap(n);
	for(int i = 0; i < n; i++){
		degreeInG[i] = G.getDegree(i);
		heap.addElement(i, degreeInG[i]);
	}
	// While the heap is not empty
	while(heap.getNumberOfElements() > 0){
		//heap.printHeap();
		std::pair<int, int> max = heap.getMax();
		// if the max is already dominated
		if(isDom[max.first]){
			heap.removeMax();
		}
		else{
			// if the current degree has changed, we update it
			if(max.second != G.getDegree(max.first)){
				heap.setMax(max.first, G.getDegree(max.first));
				heap.pushDown(0);
			}
			// otherwise we add the vertex to the dom set
			else{
				dom.push_back(max.first);
				for(int u : G.getNeighbours(max.first)){
					isDom[u] = true;
					G.disconnectVertex(u);
				}
				isDom[max.first] = true;
				G.disconnectVertex(max.first);
				heap.removeMax();
			}
		}
	}

	return dom;
}; 




std::vector<int> smarterBucketsOfBuckets(Graph G){
	std::vector<int> dom = {};
	return dom;
}; 


