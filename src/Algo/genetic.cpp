
#include "Algo/genetic.hpp"


Output large_scale_search(const Graph& G, const double &time){
	int n = G.getNumVertices();
	std::srand(std::time(0));
	std::vector<int>empty = {};
	Output best_dom = smarterBucketsOfBuckets(G, empty);
	auto start = std::chrono::high_resolution_clock::now();
	auto now = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = now - start;
	
	while(duration.count() < time){
		std::vector<int>rand_dom = best_dom.get_set();
		int pos;
		// we apply some mutations :
		for(int j = 0; j < best_dom.get_size()*0.2; j++){
			pos = rand() %  rand_dom.size();
			rand_dom[pos] = rand_dom[rand_dom.size() - 1];
			rand_dom.pop_back();
		}
		
		Output loc_dom = smarterBucketsOfBuckets(G, rand_dom);
		if(loc_dom.get_size() < best_dom.get_size()){
			best_dom = loc_dom;
		}
		now = std::chrono::high_resolution_clock::now();
		duration = now - start;
	}
	best_dom.set_runtime(time);
	return best_dom;
	
}


Output large_scale_search_with_weights(const Graph& G, const double &time, const double &alpha, const double &beta, const double &gamma, const double &lambda){
	/*
	alpha, beta in [0, 1]
	Let X_i be the solution computed at step i.
	Let p_i_x = beta[(1 - (sum X_i containing x of |x_i|)/(sum i of |X_i|))(alpha^i) + ((sum X_i containing x of 1)/(sum of X_i containing x of |X_i|))(1 - alpha^i)]
		sum X_i containing x of 1
		sum of X_i containing x of |X_i|
		sum i of |X_i|

	base : 	alpha  = 0.99
			beta   = 0.2
			gamma  = 10
			lambda = 2
	*/
	auto start = std::chrono::high_resolution_clock::now();
	auto now = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = now - start;
	int n = G.getNumVertices();
	std::vector<int> sol_containing_v(n, 0);
	std::vector<int> size_of_sol_containing_v(n, 0);
	std::srand(std::time(0));

	std::vector<int>empty = {};
	Output last_dom = smarterBucketsOfBucketsV2(G, empty);
	Output best_dom;
	best_dom.set_output(last_dom.get_set());
	int best_dom_size = best_dom.get_size();

	for(int v : best_dom.get_set()){
		sol_containing_v[v]++;
		size_of_sol_containing_v[v] = size_of_sol_containing_v[v] + best_dom_size;
	}
	int cpt = 0;
	while(duration.count() < time){
		std::vector<int> incomplete_dom = {};
		for(int v : last_dom.get_set()){
			double p = std::pow(alpha, static_cast<double>(cpt)/gamma)*beta + (1 - std::pow(alpha, cpt/gamma))*pow(lambda, 1 - (static_cast<double>(best_dom_size)/(size_of_sol_containing_v[v]/sol_containing_v[v])))*beta;
			double random_num = static_cast<double>(std::rand()) / RAND_MAX;
			if(p <= random_num){
				incomplete_dom.push_back(v);
			}
		}
		last_dom = smarterBucketsOfBucketsV2(G, incomplete_dom);
		if(last_dom.get_size() < best_dom_size){
			best_dom_size = last_dom.get_size();
			best_dom = last_dom;
		}
		cpt++;
		// Update the scores
		for(int v : last_dom.get_set()){
			size_of_sol_containing_v[v] = size_of_sol_containing_v[v] + last_dom.get_size();
			sol_containing_v[v]++;
		}
		now = std::chrono::high_resolution_clock::now();
		duration = now - start;
		std::cout << best_dom_size << " | " << last_dom.get_size() << " | " << cpt << std::endl;
	}
	best_dom.set_runtime(time);
	return best_dom;
}

