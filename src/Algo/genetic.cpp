
#include "Algo/genetic.hpp"



std::vector<int> gradient(const Graph& G, int numberOfIteration){
	std::cout << "yo\n";
	int n = G.getNumVertices();
	srand (time(NULL));
	Graph Gprime(G);
	std::vector<int>best_dom = smarterBucketsOfBuckets(&Gprime, {});
	for(int i = 0; i < numberOfIteration; i++){
		int pos = rand() %  n;
		std::cout << "\npos: " << pos << "\n";
		Graph G_loc(G);
		std::vector<int>loc_dom = smarterBucketsOfBuckets(&G_loc, forcedVertices);
		if(loc_dom.size() < best_dom.size()){
			best_dom = loc_dom;
		}
		else{
			forcedVertices[pos] = !forcedVertices[pos];
		}
		std::cout << loc_dom.size() << std::endl;
		std::cout << best_dom.size() << std::endl;
	}
	return best_dom;
}

std::vector<int> gradient(const Graph& G, int numberOfIteration){
	int n = G.getNumVertices();
	srand (time(NULL));
	Graph Gprime(G);
	std::vector<int>best_dom = smarterBucketsOfBuckets(&Gprime, {});
	return best_dom;
	/*
	for(int i = 0; i < numberOfIteration; i++){
		std::vector<int>rand_dom = best_dom;
		int pos;
		// we apply some mutations :
		for(int j = 0; j < best_dom.size()*0.2; j++){
			pos = rand() %  n;
		}
		
		Graph G_loc(G);
		std::vector<int>loc_dom = smarterBucketsOfBuckets(&G_loc, forcedVertices);
		if(loc_dom.size() < best_dom.size()){
			best_dom = loc_dom;
		}
		else{
			forcedVertices[pos] = !forcedVertices[pos];
		}
		std::cout << loc_dom.size() << std::endl;
		std::cout << best_dom.size() << std::endl;
	}
	return best_dom;
	*/
}