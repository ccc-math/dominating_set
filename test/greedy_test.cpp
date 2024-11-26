

#include "Algo/greedy.hpp"

#include <string>
#include <gtest/gtest.h>



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


TEST(greedy,hidden_instances)
{
    for(int i = 1; i <= 130; i++){
        std::string filename = "../data/pace_2016_instances/hidden/"+std::to_string(i)+".graph";
        Graph G3(filename);
        std::vector<int> tmpG3 = smarterGreedyHeap(G3);

        Graph G4(filename);
        std::vector<int> tmpG4 = smarterBucketsOfBuckets(G4);

        EXPECT_EQ(isDominatingSet(G3, tmpG3), true);
        EXPECT_EQ(isDominatingSet(G4, tmpG4), true);
    }
}


TEST(greedy,public_instances)
{
    for(int i = 1; i <= 100; i++){
        std::string str = std::to_string(i);
        if(str.size() == 2){
            str = "0"+str;
        }
        if(str.size() == 1){
            str = "00"+str;
        }
        std::string filename = "../data/pace_2016_instances/public/"+str+".graph";
        Graph G3(filename);
        std::vector<int> tmpG3 = smarterGreedyHeap(G3);

        Graph G4(filename);
        std::vector<int> tmpG4 = smarterBucketsOfBuckets(G4);

        EXPECT_EQ(isDominatingSet(G3, tmpG3), true);
        EXPECT_EQ(isDominatingSet(G4, tmpG4), true);
    }

}