#include "data_types/buckets.hpp"

///////////////////////////////////
// Methods for Buckets of Buckets
///////////////////////////////////

// Constructor
BucketsOfBuckets::BucketsOfBuckets(const Graph& G){
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