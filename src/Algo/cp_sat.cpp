#include "Algo/cp_sat.hpp"

#include "ortools/base/logging.h"
#include "ortools/sat/cp_model.h"
#include "ortools/sat/cp_model.pb.h"
#include "ortools/sat/cp_model_solver.h"
#include "ortools/util/sorted_interval_list.h"

std::vector<int> dominating_set::cp_sat(const Graph& graph)
{
    operations_research::sat::CpModelBuilder cp_model;

    std::vector<int> solution;
    return solution;
}
