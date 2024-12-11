/*
    THERE IS CURRENTLY A PROBLEM WITH DEPENDENCIES THAT NEEDS TO BE FIXED.

    THE ALGORITHM IS CURRENTLY IN COMMENT, WHILE THE CODE IN THE FUNCTION IS THE TOY EXAMPLE
    COMING FROM OR-TOOLS.


*/





#include "Algo/cp_sat.hpp"
using namespace operations_research::sat; // Temporary only for the toy example

std::vector<int> cp_sat(const Graph& G) {
    /* ACTUAL PROGRAM, BUT FIRST, TRY WITH TOY EXAMPLE BELOW
    operations_research::sat::CpModelBuilder model; // Creating the model
    int n = G.getNumVertices();
    // Boolean vector containing the variables for the cp_sat algorithm
    std::vector<operations_research::sat::BoolVar> isDominating = {}; 
    isDominating.reserve(n);
    std::vector<int> dom = {};

    // Creating the set of variables for the CP-SAT
    for (int i = 0; i < n; i++){
        isDominating.push_back(model.NewBoolVar().WithName(std::to_string(i)));
    }

    // Adding Clauses constraints
    for (int i = 0; i < n; i++){
        std::vector<int> tmp = G.getNeighbours(i);
        tmp.push_back(i);

        // Creating a clause using Boolean variables from isDominating
        std::vector<operations_research::sat::BoolVar> clause = {};
        for (int j = 0; j < tmp.size(); j++) {
            clause.push_back(isDominating[tmp[j]]);
        }

        model.AddBoolOr(clause);
    }

    // Execute the solver
    const operations_research::sat::CpSolverResponse response = Solve(model.Build());

    if (response.status() == operations_research::sat::CpSolverStatus::OPTIMAL ||
        response.status() == operations_research::sat::CpSolverStatus::FEASIBLE) {
        if (response.status() == operations_research::sat::CpSolverStatus::OPTIMAL) {
            LOG(INFO) << "Optimal solution.";
        }

        // If a solution is found is at least feasible
        for (int i = 0; i < n; i++){
            if (operations_research::sat::SolutionBooleanValue(response, isDominating[i])) {
                dom.push_back(i);
            }
        }

    } else {
        LOG(INFO) << "No solution found.";
    }

    return dom;*/

  CpModelBuilder cp_model;

  const operations_research::Domain domain(0, 2);
  const IntVar x = cp_model.NewIntVar(domain).WithName("x");
  const IntVar y = cp_model.NewIntVar(domain).WithName("y");
  const IntVar z = cp_model.NewIntVar(domain).WithName("z");

  cp_model.AddNotEqual(x, y);

  // Solving part.
  const CpSolverResponse response = Solve(cp_model.Build());

  if (response.status() == CpSolverStatus::OPTIMAL ||
      response.status() == CpSolverStatus::FEASIBLE) {
    // Get the value of x in the solution.
    LOG(INFO) << "x = " << SolutionIntegerValue(response, x);
    LOG(INFO) << "y = " << SolutionIntegerValue(response, y);
    LOG(INFO) << "z = " << SolutionIntegerValue(response, z);
  } else {
    LOG(INFO) << "No solution found.";
  }

    std::vector<int> dom = {};
    return dom;
}
