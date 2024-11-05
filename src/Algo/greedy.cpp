
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


