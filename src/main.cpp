#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Graph/graph.hpp"
#include "Algo/greedy.hpp"

int main(){
    std::string filename = "../data/pace_2016_instances/hidden/1.graph";

    Graph G1(filename);
    std::vector<int> tmpG = greedy(G1);
    for(int i = 0; i < tmpG.size(); i++){
        std::cout << tmpG[i] << " ";
    }
    std::cout << std::endl;
    
    Graph G2(filename);
    tmpG = smartGreedy(G2);
    for(int i = 0; i < tmpG.size(); i++){
        std::cout << tmpG[i] << " ";
    }
    std::cout << std::endl;

    Graph G3(filename);
    tmpG = smarterGreedyHeap(G3);
    for(int i = 0; i < tmpG.size(); i++){
        std::cout << tmpG[i] << " ";
    }
    std::cout << std::endl;

    Graph G4(filename);
    tmpG = smarterBucketsOfBuckets(G4);
    for(int i = 0; i < tmpG.size(); i++){
        std::cout << tmpG[i] << " ";
    }
    std::cout << std::endl;
    return 0;
};