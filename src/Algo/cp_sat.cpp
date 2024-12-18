#include "Algo/cp_sat.hpp"

Output cp_sat(const Graph& G, const double& time) {
    Output dom;
    operations_research::sat::CpModelBuilder model; // Creating the model
    int n = G.getNumVertices();
    // Boolean vector containing the variables for the cp_sat algorithm
    std::vector<operations_research::sat::BoolVar> isDominating = {}; 
    isDominating.reserve(n);

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

    // Minimizing the number of elements in the dominating set
    model.Minimize(operations_research::sat::LinearExpr::Sum(isDominating));

    // Sets a time limit
    operations_research::sat::Model model_parameters;
    operations_research::sat::SatParameters parameters;
    parameters.set_max_time_in_seconds(time);
    model_parameters.Add(NewSatParameters(parameters));

    // Execute the solver
    const operations_research::sat::CpSolverResponse response = SolveCpModel(model.Build(), &model_parameters);

    if (response.status() == operations_research::sat::CpSolverStatus::OPTIMAL ||
        response.status() == operations_research::sat::CpSolverStatus::FEASIBLE) {
        if (response.status() == operations_research::sat::CpSolverStatus::OPTIMAL) {
            std::cout << "Optimal solution." << std::endl;
        }
        // If a solution is found is at least feasible
        for (int i = 0; i < n; i++){
            if (operations_research::sat::SolutionBooleanValue(response, isDominating[i])) {
                dom.add(i);
            }
        }
    } else {
        std::cout << "No solution found." << std::endl;
    }

    return dom;
}

