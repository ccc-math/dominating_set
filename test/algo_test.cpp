

#include "Algo/greedy.hpp"
#include "Algo/genetic.hpp"

#include <string>
#include <gtest/gtest.h>
#include <iostream>



bool isDominatingSet(Graph G, std::vector<int> dom){
    std::vector<int> isDominated = {};
    for(int i = 0; i < G.getNumVertices(); i++){
        isDominated.push_back(false);
    }
    for(int v : dom){
        for(int nei : G.getNeighbours(v)){
            isDominated[nei] = true;
        }
        isDominated[v] = true;
    }
    for(bool b : isDominated){
        if(!b){
            return false;
        }
    }
    return true;
}


TEST(greedy,hidden_instances_Heap)
{
    for(int i = 1; i <= 130; i++){ //130
        std::string filename = "../data/fvs_h_"+std::to_string(i)+".graph";
        const Graph G3(filename);
        Output tmpG3 = smarterGreedyHeapV2(G3);

        EXPECT_EQ(isDominatingSet(G3, tmpG3.get_set()), true);
    }
}



TEST(greedy,public_instances_Heap)
{
    for(int i = 1; i <= 100; i++){
        std::string str = std::to_string(i);
        if(str.size() == 2){
            str = "0"+str;
        }
        if(str.size() == 1){
            str = "00"+str;
        }
        std::string filename = "../data/fvs_p_"+str+".graph";
        const Graph G3(filename);
        Output tmpG3 = smarterGreedyHeapV2(G3);

        EXPECT_EQ(isDominatingSet(G3, tmpG3.get_set()), true);
    }
}

TEST(greedy,hidden_instances_Buckets)
{
    for(int i = 1; i <= 130; i++){ //130
        std::string filename = "../data/fvs_h_"+std::to_string(i)+".graph";
        const Graph G3(filename);
        std::vector<int>empty = {};
        Output tmpG3 = smarterBucketsOfBucketsV2(G3, empty);

        EXPECT_EQ(isDominatingSet(G3, tmpG3.get_set()), true);
    }
}



TEST(greedy,public_instances_Buckets)
{
    for(int i = 1; i <= 100; i++){
        std::string str = std::to_string(i);
        if(str.size() == 2){
            str = "0"+str;
        }
        if(str.size() == 1){
            str = "00"+str;
        }
        std::string filename = "../data/fvs_p_"+str+".graph";
        const Graph G3(filename);
        std::vector<int>empty = {};
        Output tmpG3 = smarterBucketsOfBucketsV2(G3, empty);

        EXPECT_EQ(isDominatingSet(G3, tmpG3.get_set()), true);
    }
}


TEST(greedy,hidden_instances_Large_Scale_Search)
{
    for(int i = 1; i <= 130; i++){ //130
        std::string filename = "../data/fvs_h_"+std::to_string(i)+".graph";
        const Graph G3(filename);
        Output tmpG3 = large_scale_search(G3, 0.1);

        EXPECT_EQ(isDominatingSet(G3, tmpG3.get_set()), true);
    }
}

TEST(greedy,hidden_instances_Large_Scale_Search_weights)
{
    for(int i = 10; i <= 10; i++){ //130
        std::string filename = "../data/fvs_h_"+std::to_string(i)+".graph";
        const Graph G3(filename);
        Output tmpG3 = large_scale_search_with_weights(G3, 1.0, 0.99, 0.2, 10.0, 2.0);

        EXPECT_EQ(isDominatingSet(G3, tmpG3.get_set()), true);
    }
}


