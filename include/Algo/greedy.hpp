#ifndef GREEDY_H
#define GREEDY_H


#include <vector>
#include <utility>
#include <iostream>
#include <chrono>
#include "data_types/graph.hpp"
#include "data_types/binaryHeap.hpp"
#include "data_types/buckets.hpp"
#include "data_types/output.hpp"



Output greedy(Graph G);

Output smartGreedy(Graph G);


Output smarterGreedyHeap(Graph* G);

Output smarterGreedyHeapV2(const Graph& G);


Output smarterBucketsOfBuckets(const Graph& G, std::vector<int> &forcedVertices);

Output smarterBucketsOfBucketsV2(const Graph& G, std::vector<int> &forcedVertices);




#endif