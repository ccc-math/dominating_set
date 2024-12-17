
#include "Algo/genetic.hpp"





std::vector<int> gradient(const Graph& G, int numberOfIteration){
	int n = G.getNumVertices();
	srand (time(NULL));
	const Graph Gprime(G);
	std::vector<int>best_dom = smarterBucketsOfBuckets(Gprime, {});
	
	for(int i = 0; i < numberOfIteration; i++){
		std::vector<int>rand_dom = best_dom;
		int pos;
		// we apply some mutations :
		for(int j = 0; j < best_dom.size()*0.2; j++){
			pos = rand() %  rand_dom.size();
			rand_dom[pos] = rand_dom[rand_dom.size() - 1];
			rand_dom.pop_back();
		}
		
		const Graph G_loc(G);
		std::vector<int> loc_dom = smarterBucketsOfBuckets(G_loc, rand_dom);
		if(loc_dom.size() < best_dom.size()){
			best_dom = loc_dom;
		}
	}
	return best_dom;
	
}
