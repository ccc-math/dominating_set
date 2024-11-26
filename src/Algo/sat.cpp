/* Algorithm that solve the dominating set problem using the CP-SAT from OR-Tools library */
#include "Algo/sat.hpp"
#include ""


std::vector<int> sat(Graph G){
    CpModelBuilder model; // Creating the model
    std::vector<std::vector<int>> Clauses = {};
    int n = G.getNumVertices();
    std::vector<BoolVar> isDominating = {}; // Chaque coordonnée doit représenter le booleen correspondant à la sortie du solver
    std::vector<int> dominatingSet = {};
    isDominating.reserve(n);

    // Creating the set of variables for the CP-SAT
    for (int i = 0, i < n; i++){
        isDominating.push_back(model.NewBoolVar().WithName(std::to_string(i)));
    }

    // Adding clauses constraints
    for (int i = 0; i < n; i++){
        Clauses.push_back[G.getNeighbours(i)];
        Clauses[Clauses.size()-1].push_back(i);
        // Adding a clause to the model
        model.AddBoolOr(Clauses[Clauses.size()-1]);
    }
    
    // Execute the solver
    const CpSolverResponse response = Solve(model.Build());

    if (response.status() == CpSolverStatus::OPTIMAL ||
        response.status() == CpSolverStatus::FEASIBLE) {

        if response.status() == CpSolverStatus::OPTIMAL {
            LOG(INFO << "Optimal solution.")
        }
        // If a solution is found is at least feasible
        for (int i = 0; i < n; i++){
            if SolutionBooleanValue(response, to_string(i)) {
                dominatingSet.push_back(i);
            }
        }
    } else {
        LOG(INFO) << "No solution found.";
    }
    
    return dominatingSet;
}
