#pragma once

#include "data_types/graph.hpp"
#include "data_types/binaryHeap.hpp"
#include "data_types/buckets.hpp"

namespace dominating_set
{

std::vector<int> cp_sat(const Graph& graph);

}
