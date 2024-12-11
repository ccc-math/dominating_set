#ifndef MILP_H
#define MILP_H


#include <vector>
#include <utility>
#include <iostream>
#include "data_types/graph.hpp"
#include <Highs.h>



std::vector<int>milp(const Graph& G, const double& time);


#endif