#ifndef SAT_H
#define SAT_H

#include <stdlib.h>
#include "data_types/graph.hpp"
#include "or-tools/base/logging.h"
#include "or-tools/sat/cp_model.h"
#include "or-tools/sat/cp_model.pb.h"
#include "or-tools/sat/cp_model_solver.h"
#include "or-tools/sat/model.h"
#include "or-tools/sat/sat_parameters.pb.h"
#include "or-tools/util/sorted_interval_list.h"

std::vector<int>sat(Graph G);

#endif