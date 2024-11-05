
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
