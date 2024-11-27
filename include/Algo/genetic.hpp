#ifndef GENETIC_H
#define GENETIC_H


#include <vector>
#include <utility>
#include <iostream>
#include <stdlib.h>
#include "data_types/graph.hpp"
#include "data_types/binaryHeap.hpp"
#include "data_types/buckets.hpp"
#include "Algo/greedy.hpp"



std::vector<int> gradient(const Graph& G, int numberOfIteration);



#endif