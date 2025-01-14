#ifndef GENETIC_H
#define GENETIC_H


#include <vector>
#include <utility>
#include <iostream>
#include <cmath>
#include <chrono>
#include <stdlib.h>
#include "data_types/graph.hpp"
#include "data_types/binaryHeap.hpp"
#include "data_types/buckets.hpp"
#include "data_types/output.hpp"
#include "Algo/greedy.hpp"


Output large_scale_search(const Graph& G, double time);

Output large_scale_search_with_weights(const Graph& G, double time, double alpha, double beta, double gamma, double lambda);



#endif