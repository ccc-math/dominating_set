#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Graph/graph.hpp"
#include "Algo/greedy.hpp"

int main(){
    
    Graph G("../data/project_instances/4.graph");
    std::vector<int> tmpG = greedy(G);
    for(int i = 0; i < tmpG.size(); i++){
        std::cout << tmpG[i] << " ";
    }
    std::cout << std::endl;
    


    Graph H("../data/project_instances/4.graph");
    std::vector<int> tmpH = smartGreedy(H);
    for(int i = 0; i < tmpH.size(); i++){
        std::cout << tmpH[i] << " ";
    }
    std::cout << std::endl;
    return 0;
};