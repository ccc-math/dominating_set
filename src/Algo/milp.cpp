#include "Algo/milp.hpp"



std::vector<int> milp(Graph G){
    std::vector<int> dom = {};
    int n = G.getNumVertices(); // Cardinal de V
    std::vector<std::vector<int>> adj = {}; // Vecteurs de binaire listes d'adjacences pour le sommet i
    for (int i = 0; i < n; i++){
        std::vector<int> tmp = {};
        std::vector<int> neighbors = G.getNeighbours(i);
        neighbors.push_back(i);
        for (int j = 0; j < n; j++){
            if(std::find(neighbors.begin(), neighbors.end(), j) != neighbors.end()) {
                tmp.push_back(1);
            } else {
                tmp.push_back(0);
            }
        }
        adj.push_back(tmp);
    }
    std::vector<double> zeros(n, 0);
    std::vector<double> ones(n, 1); // Vectors of size n filled with 1
    std::vector<double> upper(n, n);

    HighsModel model;
    model.lp_.num_col_ = n;
    model.lp_.num_row_ = n;
    model.lp_.offset_ = 0;
    model.lp_.sense_ = ObjSense::kMinimize;
    model.lp_.col_cost_ = ones;
    model.lp_.col_lower_ = zeros;
    model.lp_.col_upper_ = ones;
    model.lp_.row_lower_ = ones;
    model.lp_.row_upper_ = upper;
    model.lp_.a_matrix_.format_ = MatrixFormat::kColwise;

    // Prepare the sparse matrix
    std::vector<int> start(n + 1, 0);   // Start index for each column (size = num_col_ + 1)
    std::vector<int> index;             // Row indices for non-zero values
    std::vector<double> value;          // Values of the non-zero elements

    // Fill start, index, and value vectors based on your adjacency matrix
    int nonzero_count = 0;
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            if (adj[i][j] == 1) {  // If there is an edge between i and j
                index.push_back(i);    // Add row index
                value.push_back(1.0);  // Add the corresponding value (1.0 for adjacency)
                nonzero_count++;
            }
        }
        start[j + 1] = nonzero_count;  // Update the start index for column j+1
    }

    // Set the sparse matrix in HiGHS model
    model.lp_.a_matrix_.start_ = start;
    model.lp_.a_matrix_.index_ = index;
    model.lp_.a_matrix_.value_ = value;

    Highs highs;
    HighsStatus return_status;
    //
    // Pass the model to HiGHS
    return_status = highs.passModel(model);
    //assert(return_status == HighsStatus::kOk);
    // If a user passes a model with entries in
    // model.lp_.a_matrix_.value_ less than (the option)
    // small_matrix_value in magnitude, they will be ignored. A logging
    // message will indicate this, and passModel will return
    // HighsStatus::kWarning
    //
    // Get a const reference to the LP data in HiGHS
    const HighsLp& lp = highs.getLp();
    //
    // Solve the model
    return_status = highs.run();
    //assert(return_status == HighsStatus::kOk);
    //
    // Get the model status
    const HighsModelStatus& model_status = highs.getModelStatus();
    //assert(model_status == HighsModelStatus::kOptimal);
    //std::cout << "Model status: " << highs.modelStatusToString(model_status) << std::endl;
    //
    // Get the solution information
    const HighsInfo& info = highs.getInfo();
    //std::cout << "Simplex iteration count: " << info.simplex_iteration_count << std::endl;
    //std::cout << "Objective function value: " << info.objective_function_value << std::endl;
    //std::cout << "Primal  solution status: " << highs.solutionStatusToString(info.primal_solution_status) << std::endl;
    //std::cout << "Dual    solution status: " << highs.solutionStatusToString(info.dual_solution_status) << std::endl;
    //std::cout << "Basis: " << highs.basisValidityToString(info.basis_validity) << std::endl;
    const bool has_values = info.primal_solution_status;
    const bool has_duals = info.dual_solution_status;
    const bool has_basis = info.basis_validity;
    //
    // Get the solution values and basis
    const HighsSolution& solution = highs.getSolution();
    const HighsBasis& basis = highs.getBasis();
    //
    // Report the primal and solution values and basis
    /*
    for (int col = 0; col < lp.num_col_; col++) {
        std::cout << "Column " << col;
        if (has_values) std::cout << "; value = " << solution.col_value[col];
        if (has_duals) std::cout << "; dual = " << solution.col_dual[col];
        if (has_basis) std::cout << "; status: " << highs.basisStatusToString(basis.col_status[col]);
        std::cout << std::endl;
    }
    for (int row = 0; row < lp.num_row_; row++) {
        std::cout << "Row    " << row;
        if (has_values) std::cout << "; value = " << solution.row_value[row];
        if (has_duals) std::cout << "; dual = " << solution.row_dual[row];
        if (has_basis) std::cout << "; status: " << highs.basisStatusToString(basis.row_status[row]);
        std::cout << std::endl;
    }
    */

    // Now indicate that all the variables must take integer values
    model.lp_.integrality_.resize(lp.num_col_);
    for (int col = 0; col < lp.num_col_; col++)
        model.lp_.integrality_[col] = HighsVarType::kInteger;

    highs.passModel(model);
    // Solve the model
    return_status = highs.run();
    //assert(return_status == HighsStatus::kOk);
    // Report the primal solution values
    for (int col = 0; col < lp.num_col_; col++) {
        //std::cout << "Column " << col;
        if (info.primal_solution_status)
            //std::cout << "; value = " << solution.col_value[col];
            if (solution.col_value[col] > 0.1) {
                dom.push_back(col);
            }
        //std::cout << std::endl;
    }
    for (int row = 0; row < lp.num_row_; row++) {
        //std::cout << "Row    " << row;
        if (info.primal_solution_status) {}
        //std::cout << "; value = " << solution.row_value[row];
        //std::cout << std::endl;
    }

    std::cout << n << std::endl;
    return dom;
}