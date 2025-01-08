#pragma once

#include <stdlib.h>
#include <chrono>


//Data dependencies
#include "data_types/graph.hpp"
#include "data_types/binaryHeap.hpp"
#include "data_types/buckets.hpp"
#include "data_types/output.hpp"


//Or tools dependencies
#include "absl/container/btree_map.h"
#include "absl/container/btree_set.h"
#include "absl/flags/flag.h"
#include "absl/log/check.h"
#include "absl/strings/str_cat.h"
#include "absl/types/span.h"
#include "google/protobuf/text_format.h"
#include "ortools/base/init_google.h"
#include "ortools/base/logging.h"
#include "ortools/base/path.h"
#include "ortools/packing/binpacking_2d_parser.h"
#include "ortools/packing/multiple_dimensions_bin_packing.pb.h"
#include "ortools/sat/cp_model.h"
#include "ortools/sat/cp_model.pb.h"
#include "ortools/sat/cp_model_solver.h"
#include "ortools/sat/sat_parameters.pb.h"
#include "ortools/sat/util.h"
#include "ortools/util/sorted_interval_list.h"


Output cp_sat(const Graph& G, const double& time);
