#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Graph/graph.hpp"
#include "Algo/greedy.hpp"

int main() {
    
    Graph G("../data/pace_2016_instances/hidden/1.graph");
    std::vector<int> tmp = greedy(G);
    std::cout << tmp.size() << std::endl;
    return 0;
};