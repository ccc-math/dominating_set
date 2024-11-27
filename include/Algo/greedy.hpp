#ifndef GREEDY_H
#define GREEDY_H


#include <vector>
#include <utility>
#include <iostream>
#include "data_types/graph.hpp"
#include "data_types/binaryHeap.hpp"
#include "data_types/buckets.hpp"



std::vector<int>greedy(Graph G);

std::vector<int>smartGreedy(Graph G);



std::vector<int>smarterGreedyHeap(Graph* G);


std::vector<int>smarterBucketsOfBuckets(Graph* G, std::vector<bool> forcedVertices);




#endif