
#include "Algo/genetic.hpp"



std::vector<int> gradient(Graph G, int numberOfIteration){
	std::vector<int> dom = smarterBucketsOfBuckets(G);
	for(int i = 0; i < numberOfIteration; i++){
		dom = smarterBucketsOfBuckets(G);	
	}
	return dom;
}