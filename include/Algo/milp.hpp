#ifndef MILP_H
#define MILP_H


#include <vector>
#include <utility>
#include <iostream>
#include "data_types/graph.hpp"
#include "data_types/output.hpp"
#include <Highs.h>



Output milp(const Graph& G, const double& time);


#endif