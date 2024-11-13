#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Graph/graph.hpp"
#include "Algo/greedy.hpp"
#include "Algo/genetic.hpp"

int main(){
    //std::string filename = "../data/project_instances/5.graph";
    //std::string filename = "../data/pace_2016_instances/hidden/31.graph";
    //std::string filename = "../data/pace_2016_instances/hidden/1.graph";
    //std::string filename = "../data/pace_2016_instances/hidden/3.graph"; 


    std::string filename;
    bool printlist = false;
    bool printsize = false;
    int numRepet = 100;
    int algo = 3; 

    for(int j = 1; j <= numRepet; j++){
        std::string filename = "../data/pace_2016_instances/public/037.graph"; 
        std::cout << j << "/" << numRepet << std::endl;
        if(algo == 3){
            Graph G3(filename);
            std::vector<int> tmpG3 = smarterGreedyHeap(G3);
            if(printlist){
                for(int i = 0; i < tmpG3.size(); i++){
                    std::cout << tmpG3[i] << " ";
                }
                std::cout << std::endl;
            }
            if(printsize){
                std::cout << tmpG3.size() << std::endl;
                std::cout << std::endl;
            }
        }
        else if(algo == 4){
            Graph G4(filename);
            std::vector<int> tmpG4 = smarterBucketsOfBuckets(G4);
            if(printlist){
                for(int i = 0; i < tmpG4.size(); i++){
                    std::cout << tmpG4[i] << " ";
                }
                std::cout << std::endl;
            }
            if(printsize){
                std::cout << tmpG4.size() << std::endl;
                std::cout << std::endl;
            }
        }
    }
    return 0;
};