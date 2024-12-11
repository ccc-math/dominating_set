#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "data_types/graph.hpp"
#include "Algo/greedy.hpp"
#include "Algo/genetic.hpp"
#include "Algo/milp.hpp"
#include "Algo/cp_sat.hpp"

int main(){
    //std::string filename = "../data/project_instances/5.graph";
    //std::string filename = "../data/pace_2016_instances/hidden/31.graph";
    //std::string filename = "../data/pace_2016_instances/hidden/1.graph";
    //std::string filename = "../data/pace_2016_instances/hidden/3.graph"; 

/*
    std::string filename;
    bool printlist = false;
    bool printsize = true;
    int algo = 0; 

    for(int i = 10; i <= 10; i++){
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
            Graph G3(filename);
            std::vector<int> tmpG3 = smarterGreedyHeapV2(&G3);
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


        if(algo == 5 || algo == 0){
            Graph G4(filename);
            int n = G4.getNumVertices();
            std::vector<int> tmpG4 = smarterBucketsOfBuckets(&G4, {});
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

        if(algo == 7 || algo == 0){
            Graph G5(filename);
            std::vector<int> tmpG5 = gradient(G5, 1000);
            if(printlist){
                for(int i = 0; i < tmpG5.size(); i++){
                    std::cout << tmpG5[i] << " ";
                }
                std::cout << std::endl;
            }
            if(printsize){
                std::cout << tmpG5.size() << std::endl;
                std::cout << std::endl;
            }
        }
    }
    filename = "../data/pace_2016_instances/public/090.graph"; 
    Graph G(filename);

    std::vector<int> test= milp(G);
    std::cout << std::endl;
    std::cout << std::endl;
    //std::cout << test.size() << std::endl;
    std::cout << std::endl;
    for(int i; i < test.size(); i++){
        //std::cout << test[i] << std::endl;
    }
*/

    std::string filename_cp_sat = "../data/project_instances/5.graph";
    Graph G_cp_sat(filename);

    std::vector<int> test_cp_sat = cp_sat(G_cp_sat);
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << test_cp_sat.size() << std::endl;
    std::cout << std::endl;
    for(int i; i < test_cp_sat.size(); i++){
        std::cout << test_cp_sat[i] << std::endl;
    }


    return 0;
};