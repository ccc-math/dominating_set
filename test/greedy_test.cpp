

#include "Algo/greedy.hpp"
#include <gtest/gtest.h>



TEST(greedy,template)
{
    std::string filename = "../data/project_instances/5.graph";
    Graph G(filename);
    BucketsOfBuckets buckets(&G);
    for(int i = 0; i < buckets.getNumberOfElements(); i++){
        buckets.pushVertexUp(i, G.getDegree(i));
    }
    buckets.pushVertexUp(0, 9);
    buckets.decreaseVertex(15);
    buckets.decreaseVertex(15);

    int a = 1;
    EXPECT_EQ(a, 1);

}