
#include "data_types/graph.hpp"
#include <gtest/gtest.h>

TEST(Graph,test1)
{
    Graph G_1(10000);
    Graph G_2("./data/project_instances/3.graph");
    G_1.addEdge(25,5000);
    EXPECT_EQ(G_1.hasEdge(25,5000),true);
    EXPECT_EQ(G_1.hasEdge(1,3600),false);
    EXPECT_EQ(G_1.getNumVertices(),10000);

    EXPECT_EQ(G_2.getNumVertices(),12);
    EXPECT_EQ(G_2.hasEdge(0,1),true);

}