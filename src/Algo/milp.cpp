#include "Algo/milp.hpp"


std::vector<int> milp(const Graph& G, const double& time){
    std::vector<int> dom = {};
    const int n = G.getNumVertices();
    std::vector<std::vector<int>> adj = {}; // Vector containing all adjacency lists
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

    highs.setOptionValue("time_limit", time);

    HighsStatus return_status;

    // Pass the model to HiGHS
    return_status = highs.passModel(model);

    const HighsLp& lp = highs.getLp();

    // Solve the model
    return_status = highs.run();

    // Get the solution information
    const HighsInfo& info = highs.getInfo();

    // Get the solution values and basis
    const HighsSolution& solution = highs.getSolution();

    // Now indicate that all the variables must take integer values
    model.lp_.integrality_.resize(lp.num_col_);
    for (int i = 0; i < lp.num_col_; i++)
        model.lp_.integrality_[i] = HighsVarType::kInteger;

    highs.passModel(model);

    // Solve the model
    return_status = highs.run();

    for (int i = 0; i < lp.num_col_; i++) {
        if (info.primal_solution_status && solution.col_value[i] > 0.1) {
                dom.push_back(i);
            }
    }

    return dom;
}
