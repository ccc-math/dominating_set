
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
};

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
	std::pair<int, int> max;
	while(heap.getNumberOfElements() > 0){
		//heap.printHeap();
		max = heap.getMax();
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

///////////////////////////////////
// Methods for Buckets of Buckets
///////////////////////////////////

// Constructor
BucketsOfBuckets::BucketsOfBuckets(Graph G){
	maxDegree = -1;
	numOfElements = G.getNumVertices();
	currentDegree = {};
	// Current degrees : 
	for(int i = 0; i < numOfElements; i++){
		currentDegree.push_back(0);  // at first, we put all vertices in bucket 0 like they were of degree 0, it will be corrected with another method
		if(maxDegree < G.getDegree(i)){
			maxDegree = G.getDegree(i);
		}
	}
	// Construction of the buckets : We put all vertices in the bucket 0, and we will correct it in another method
	heads = std::vector<int>(maxDegree + 2, -1);
	pred_bucket = std::vector<int>(maxDegree + 1, -1);
	next_bucket = std::vector<int>(maxDegree + 1, -1);
	pred_vertex = std::vector<int>(numOfElements, -1);
	next_vertex = std::vector<int>(numOfElements, -1);

	head = 0;
	heads[0] = 0;
	next_vertex[0] = 1;
	for(int i = 1; i < numOfElements - 1; i++){
		pred_vertex[i] = i - 1;
		next_vertex[i] = i + 1;
	}
	pred_vertex[numOfElements - 1] = numOfElements - 2;
};

// Methods
void BucketsOfBuckets::printBucketsOfBuckets(){
	std::cout << "max degree      : " << maxDegree << std::endl;
	std::cout << "num of elements : " << numOfElements << std::endl;
	std::cout << "head            : " << head << std::endl;
	for(int i = 0; i < numOfElements; i++){
		std::cout << "deg(" << i << ") = " << currentDegree[i] << ",  ";
	}
	std::cout << "\n\nnext_vertex :" << std::endl;
	for(int i = 0; i < numOfElements; i++){
		std::cout << "nv(" << i << ") = " <<next_vertex[i] << ",  ";
	}
	std::cout << "\n\npred_vertex :" << std::endl;
	for(int i = 0; i < numOfElements; i++){
		std::cout << "pv(" << i << ") = " << pred_vertex[i] << ",  ";
	}
	std::cout << "\n\nheads :" << std::endl;
	for(int i = 0; i < maxDegree + 1; i++){
		std::cout << "head(" << i << ") = " << heads[i] << ",  ";
	}
	std::cout << "\n\nnext_bucket :" << std::endl;
	for(int i = 0; i < maxDegree + 1; i++){
		std::cout << "nb(" << i << ") = " <<next_bucket[i] << ",  ";
	}
	std::cout << "\n\npred_bucket :" << std::endl;
	for(int i = 0; i < maxDegree + 1; i++){
		std::cout << "pb(" << i << ") = " << pred_bucket[i] << ",  ";
	}
	std::cout << std::endl;
};

void BucketsOfBuckets::printBucketsOfBucketsV2(){
	std::cout << "max degree      : " << maxDegree << std::endl;
	std::cout << "num of elements : " << numOfElements << std::endl;
	std::cout << "head            : " << head << std::endl;
	int bucket = head;
	while(bucket >= 0){
		if(heads[bucket] >= 0){
			std::cout << bucket << " | " << heads[bucket];
			int next = next_vertex[heads[bucket]];
			while(next >= 0){
				std::cout << " -> " << next;
				next = next_vertex[next];
			}
			std::cout << std::endl;
		}
		bucket = pred_bucket[bucket];
	}
};

void BucketsOfBuckets::remove_bucket(int d){
	if(pred_bucket[d] == -1){
		if(next_bucket[d] == -1){	// d was the only bucket
			head = -1;
		}
		else{
			pred_bucket[next_bucket[d]] = -1; // d was the lowest bucket
		}
	}
	else{
		if(next_bucket[d] == -1){	// d was the largest bucket
			next_bucket[pred_bucket[d]] = -1;
			head = pred_bucket[d];
		}
		else{
			pred_bucket[next_bucket[d]] = pred_bucket[d];
			next_bucket[pred_bucket[d]] = next_bucket[d];
		}
	}
	pred_bucket[d] = -1;
	next_bucket[d] = -1;
}

void BucketsOfBuckets::remove_vertex_from_bucket(int v, int d){
	currentDegree[v] = -1;
	if(heads[d] == v){
		if(next_vertex[v] == -1){ // v was alone in its bucket
			heads[d] = -1;
			remove_bucket(d);
		}
		else{
			heads[d] = next_vertex[v];
			pred_vertex[next_vertex[v]] = -1;
			pred_vertex[v] = -1;
			next_vertex[v] = -1;
		}
	}
	else{
		if(next_vertex[v] == -1){ // v was last in its bucket
			next_vertex[pred_vertex[v]] = -1;
		}
		else{
			next_vertex[pred_vertex[v]] = next_vertex[v];
			pred_vertex[next_vertex[v]] = pred_vertex[v];
			next_vertex[v] = -1;
			pred_vertex[v] = -1;
		}
	}
}

void BucketsOfBuckets::pushVertexUp(int v, int d){
	// remove v from its bucket and put it in bucket d;
	bool flag = true;
	while(currentDegree[v] != d){
		if(next_bucket[currentDegree[v]] == -1){ // we've reached the last bucket
			next_bucket[currentDegree[v]] = d;
			pred_bucket[d] = currentDegree[v];
			remove_vertex_from_bucket(v, currentDegree[v]);
			heads[d] = v;
			currentDegree[v] = d;
		}
		else{
			if(next_bucket[currentDegree[v]] > d){ // we need to add a new bucket between currentdegree and next bucket
				next_bucket[d] = next_bucket[currentDegree[v]];
				pred_bucket[next_bucket[currentDegree[v]]] = d;
				next_bucket[currentDegree[v]] = d;
				pred_bucket[d] = currentDegree[v];
				remove_vertex_from_bucket(v, currentDegree[v]);
				heads[d] = v;
				currentDegree[v] = d;
			}
			else{
				int tmp = next_bucket[currentDegree[v]];
				remove_vertex_from_bucket(v, currentDegree[v]);
				currentDegree[v] = tmp;
				next_vertex[v] = heads[tmp];
				pred_vertex[heads[tmp]] = v;
				heads[tmp] = v;
			}
		}
	}
	if(d > head){
		head = d;
	}
};
void BucketsOfBuckets::decreaseVertex(int v){
	int degV = currentDegree[v];
	if(pred_bucket[degV] == -1){ // v is in the lowest bucket
		heads[degV - 1] = v;
		pred_bucket[degV] = degV - 1;
		next_bucket[degV - 1] = degV; // bug here
		remove_vertex_from_bucket(v, degV);
		currentDegree[v] = degV - 1; 
	}
	else{
		if(pred_bucket[degV] == degV - 1){ // if the bucket deg(v) already exists
			remove_vertex_from_bucket(v, degV);
			next_vertex[v] = heads[degV - 1];
			pred_vertex[heads[degV - 1]] = v;
			heads[degV - 1] = v;
			currentDegree[v] = degV - 1;
		}
		else{ // otherwise we need to add a new bucket
			next_bucket[pred_bucket[degV]] = degV - 1;
			pred_bucket[degV - 1] = pred_bucket[degV];
			next_bucket[degV - 1] = degV;
			pred_bucket[degV] = degV - 1;
			heads[degV - 1] = v;
			remove_vertex_from_bucket(v, degV);
			currentDegree[v] = degV - 1;

		}
	}

}

void BucketsOfBuckets::deleteVertex(int v){
	remove_vertex_from_bucket(v, currentDegree[v]);
}

int BucketsOfBuckets::getNumberOfElements(){
	return numOfElements;
};
int BucketsOfBuckets::getMaxDegree(){
	return maxDegree;
};
int BucketsOfBuckets::getHead(){
	return head;
};
int BucketsOfBuckets::getHeadVertex(){
	return heads[head];
};



/////////////////////////////////////////
// Smart Greedy with Buckets of Buckets
/////////////////////////////////////////

std::vector<int> smarterBucketsOfBuckets(Graph G){
	/*
	
	Here, we store the  current degree of non-dominated vertices in a double linked list of double linked list
	a - b - d
	 \ /
	  c

	In this graph, deg(a) = deg(c) = 2, deg(b) = 3, deg(d) = 1

	The data structure is then 	3 : b
								2 : a <-> c
								1 : d

	remove an element knowing its degree : O(1)
	Global costs of updates : O(m) (m : number of edges)
	*/
	std::vector<int> dom = {};
	BucketsOfBuckets buckets(G);
	std::vector<bool> isDom = std::vector<bool>(buckets.getNumberOfElements(), false);
	for(int i = 0; i < buckets.getNumberOfElements(); i++){
		buckets.pushVertexUp(i, G.getDegree(i));
	}
	// from this points, the deta structure is fully built !
	while(buckets.getHead() >= 0){
		std::vector<int> deleted = {};
		int vertex = buckets.getHeadVertex();						
		buckets.deleteVertex(vertex);
		deleted.push_back(vertex);
		dom.push_back(vertex);
		isDom[vertex] = true;
		for(int v : G.getNeighbours(vertex)){
			if(!isDom[v]){
				buckets.deleteVertex(v);
				deleted.push_back(v);
				isDom[v] = true;
			}
		}
		for(int v : deleted){
			for(int nei : G.getNeighbours(v)){
				if(!isDom[nei]){
					buckets.decreaseVertex(nei);
				}
			}
		}
	}
	return dom;
}; 


