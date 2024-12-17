
#include "data_types/graph.hpp"
#include <gtest/gtest.h>
#include "data_types/output.hpp"


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



TEST(Output,test)
{
    Output O;
    EXPECT_EQ(O.get_size(),0);
    O.add(1);
    O.add(5);
    O.add(10);
    EXPECT_EQ(O.get_size(),3);
    EXPECT_EQ(O.is_in_set(5),true);
    EXPECT_EQ(O.is_in_set(4),false);


}