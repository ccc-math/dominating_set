
#include "Algo/greedy.hpp"






Output greedy(Graph* G){
	Output dom;
	std::vector<bool> isDom = {};
	int n = G->getNumVertices();
	for(int i = 0; i < n; i++){
		isDom.push_back(false);
	}
	for(int i = 0; i < n; i++){
		if(!isDom[i]){
			dom.add(i);
			isDom[i] = true;
			for(int u : G->getNeighbours(i)){
				isDom[u] = true;
			}
		}
	}
	return dom;
}



Output smartGreedy(Graph* G){
	int n = G->getNumVertices();
	std::vector<bool>dom(n, false);
	std::vector<bool>isDom(n, false);
	for(int i = 0; i < n; i++){
		if(G->isIsolated(i)){
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
			if(!isDom[i] && G->getDegree(i) > maxDeg){
				maxDeg = G->getDegree(i);
				maxDegVertex = i;
				flag = true;
			}
		}
		if(flag){
			dom[maxDegVertex] = true;
			isDom[maxDegVertex] = true;
			for(int u : G->getNeighbours(maxDegVertex)){
				isDom[u] = true;
				G->disconnectVertex(u);
			}
			G->disconnectVertex(maxDegVertex);
		}
	}
	Output res;
	for(int i = 0; i < n; i++){
		if(dom[i]){
			res.add(i);
		}
	}
	return res;
};



//////////////////////////////
//   Smart Greedy with Heap
//////////////////////////////

Output smarterGreedyHeap(Graph *G){
	int n = G->getNumVertices();
	std::vector<bool> isDom(n, false);
	Output dom ;
	std::vector<int> degreeInG(n, 0);
	BinaryHeap heap(n);
	for(int i = 0; i < n; i++){
		degreeInG[i] = G->getDegree(i);
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
			if(max.second != G->getDegree(max.first)){
				heap.setMax(max.first, G->getDegree(max.first));
				heap.pushDown(0);
			}
			// otherwise we add the vertex to the dom set
			else{
				dom.add(max.first);
				for(int u : G->getNeighbours(max.first)){
					isDom[u] = true;
					G->disconnectVertex(u);
				}
				isDom[max.first] = true;
				G->disconnectVertex(max.first);
				heap.removeMax();
			}
		}
	}

	return dom;
}; 

Output smarterGreedyHeapV2(const Graph& G){
	/*
	Algo : We keep 3 types of vertices :
		- the black ones : in the dominating set
		- the grey ones : the dominated ones
		- and the white ones : the non-dominated ones
		At each step, we put the non-black vertex with the largest number of white vertices in the som set

	*/
	int n = G.getNumVertices();
	int nonDominated = n;					// number of white vertices
	std::vector<bool> isDom(n, false);	// if v is not white
	Output dom;
	std::vector<int> degreeInG(n, 0);		// number of current white neighbours
	BinaryHeap heap(n);
	for(int i = 0; i < n; i++){
		degreeInG[i] = G.getDegree(i);
		if(degreeInG[i] > 0)
			heap.addElement(i, degreeInG[i]);
		else{
			nonDominated--;
			dom.add(i);
		}
	}
	// While the there exists non-dominated vertices (white vertices)
	std::pair<int, int> max;
	while(nonDominated > 0){
		//std::cout << std::endl;
		//heap.printHeap();
		//std::cout << "non dom " << nonDominated << std::endl;
		max = heap.getMax();
		//std::cout << "max :               " << max.first << " " << max.second << std::endl;
		// if the current degree has changed, we update it in the heap
		if(max.second != degreeInG[max.first]){
			heap.setMax(max.first, degreeInG[max.first]);
			heap.pushDown(0);
		}
		else{
			// otherwise we add the vertex to the dom set
			dom.add(max.first);
			heap.removeMax();
			// and then we update the degrees if the chosen vertex was white
			for(int u : G.getNeighbours(max.first)){
				if(!isDom[max.first]){	// if max was white
					degreeInG[u]--;		
					if(degreeInG[u] <= 0){
						degreeInG[u] = -1;	// if u has white degree 0, we can force it to not be in the dom set since u has no non-dominated neighbours
					}
				}
				if(!isDom[u]){			// if u was white
					for(int nei : G.getNeighbours(u)){
						degreeInG[nei]--;
						if(degreeInG[nei] <= 0){
							degreeInG[nei] = -1;	// if nei has white degree 0, we can force it to not be in the dom set since nei has no non-dominated neighbours
						}
					}
					isDom[u] = true;
					nonDominated--;
				}
			}
			if(!isDom[max.first]){
				isDom[max.first] = true;
				nonDominated--;
			}
			
		}
	}

	return dom;
};





/////////////////////////////////////////
// Smart Greedy with Buckets of Buckets
/////////////////////////////////////////
Output smarterBucketsOfBuckets(const Graph& G, std::vector<int>forcedVertices){
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
	// First, we put the the forced vertices in the dom set
	Output dom;
	BucketsOfBuckets buckets(G);
	std::vector<bool> isDom = std::vector<bool>(buckets.getNumberOfElements(), false);
	for(int i = 0; i < buckets.getNumberOfElements(); i++){
		buckets.pushVertexUp(i, G.getDegree(i));
	}
	// from this points, the deta structure is fully built !
	// We can put the forced vertices in the dominant
	for(int u : forcedVertices){
		// If u has not already been dominated :
		std::vector<int> deleted = {};
		if(!isDom[u]){
			isDom[u] = true;
			dom.add(u);
			buckets.deleteVertex(u);
			deleted.push_back(u);
		}
		for(int v : G.getNeighbours(u)){
			if(!isDom[v]){
				isDom[v] = true;
				buckets.deleteVertex(v);
				deleted.push_back(v);
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

	while(buckets.getHead() >= 0){
		std::vector<int> deleted = {};
		int vertex = buckets.getHeadVertex();						
		buckets.deleteVertex(vertex);
		deleted.push_back(vertex);
		dom.add(vertex);
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



Output smarterBucketsOfBucketsV2(const Graph &G, std::vector<int>forcedVertices){
	// First, we construct the data structure
	int n = G.getNumVertices();
	int nonDominated = n;
	Output dom;
	BucketsOfBuckets buckets(G);
	std::vector<bool> isDom(n, false);
	std::vector<bool> isInDom(n, false);
	for(int i = 0; i < buckets.getNumberOfElements(); i++){
		buckets.pushVertexUp(i, G.getDegree(i));
	}
	// Then, we proceed with the algorithm
	// First, if there are some forced vertices, we put them in the dominating set
	for(int v : forcedVertices){
		dom.add(v);
		buckets.deleteVertex(v);
		isInDom[v] = true;
		for(int u : G.getNeighbours(v)){
			if(!isDom[v]){
				buckets.decreaseVertex(u);
			}
			if(!isDom[u]){
				for(int nei : G.getNeighbours(u)){
					if(!isInDom[nei]){
						buckets.decreaseVertex(nei);
					}
				}
				isDom[u] = true;
				nonDominated--;
			}
		}
		if(!isDom[v]){
			isDom[v] = true;
			nonDominated--;
		}
	}
	// Then, we run the algorithm
	while(nonDominated > 0){
		int vertex = buckets.getHeadVertex();	// Head of the structure, vertex of max white degree
		buckets.deleteVertex(vertex);
		dom.add(vertex);
		isInDom[vertex] = true;
		for(int u : G.getNeighbours(vertex)){
			if(!isDom[vertex]){	// if vertex was white
				buckets.decreaseVertex(u);
			}
			
			if(!isDom[u]){			// if u was white
				for(int nei : G.getNeighbours(u)){
					if(!isInDom[nei]){
						buckets.decreaseVertex(nei);
					}
				}
				isDom[u] = true;
				nonDominated--;
			}
		}
		if(!isDom[vertex]){
			isDom[vertex] = true;
			nonDominated--;
		}
	}
	return dom;
}; 



