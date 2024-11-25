#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "data_types/graph.hpp"
#include "Algo/greedy.hpp"
#include "Algo/genetic.hpp"

int main(){
    //std::string filename = "../data/project_instances/5.graph";
    //std::string filename = "../data/pace_2016_instances/hidden/31.graph";
    //std::string filename = "../data/pace_2016_instances/hidden/1.graph";
    //std::string filename = "../data/pace_2016_instances/hidden/3.graph"; 


    std::string filename;
    bool printlist = false;
    bool printsize = true;
    int algo = 0; 

    for(int i = 1; i <= 130; i++){
        std::string filename = "../data/pace_2016_instances/hidden/"+std::to_string(i)+".graph"; 
        std::cout << i << "/" << 130 << std::endl;
        if(algo == 3 || algo == 0){
            Graph G3(filename);
            std::vector<int> tmpG3 = smarterGreedyHeap(&G3);
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
        if(algo == 4 || algo == 0){
            Graph G4(filename);
            std::vector<int> tmpG4 = smarterBucketsOfBuckets(&G4);
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