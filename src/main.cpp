#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Graph/graph.hpp"
#include "Algo/greedy.hpp"

int main(){
    std::string filename = "../data/project_instances/4.graph";
    //std::string filename = "../data/pace_2016_instances/hidden/108.graph";
    bool printlist = true;
    bool printsize = true;

    Graph G1(filename);
    std::vector<int> tmpG = greedy(G1);
    if(printlist){
        for(int i = 0; i < tmpG.size(); i++){
            std::cout << tmpG[i] << " ";
        }
        std::cout << std::endl;
    }
    if(printsize){
        std::cout << tmpG.size() << std::endl;
        std::cout << std::endl;
    }
    
    



    Graph G2(filename);
    tmpG = smartGreedy(G2);
    if(printlist){
        for(int i = 0; i < tmpG.size(); i++){
            std::cout << tmpG[i] << " ";
        }
        std::cout << std::endl;
    }
    if(printsize){
        std::cout << tmpG.size() << std::endl;
        std::cout << std::endl;
    }





    Graph G3(filename);
    tmpG = smarterGreedyHeap(G3);
    if(printlist){
        for(int i = 0; i < tmpG.size(); i++){
            std::cout << tmpG[i] << " ";
        }
        std::cout << std::endl;
    }
    if(printsize){
        std::cout << tmpG.size() << std::endl;
        std::cout << std::endl;
    }





    Graph G4(filename);
    tmpG = smarterBucketsOfBuckets(G4);
    if(printlist){
        for(int i = 0; i < tmpG.size(); i++){
            std::cout << tmpG[i] << " ";
        }
        std::cout << std::endl;
    }
    if(printsize){
        std::cout << tmpG.size() << std::endl;
        std::cout << std::endl;
    }
    return 0;
};