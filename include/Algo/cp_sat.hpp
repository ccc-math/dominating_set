#pragma once

#include "data_types/graph.hpp"
#include "data_types/binaryHeap.hpp"
#include "data_types/buckets.hpp"
#include "ortools/base/logging.h"
#include "ortools/sat/cp_model.h"
#include "ortools/sat/cp_model.pb.h"
#include "ortools/sat/cp_model_solver.h"
#include "ortools/util/sorted_interval_list.h"

std::vector<int> cp_sat(const Graph& G);
