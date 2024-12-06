#include "Algo/milp.hpp"



std::vector<int> milp(Graph G){

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

    HighsModel milp;
    milp.lp_.num_col_ = n;
    milp.lp_.num_row_ = n;
    milp.lp_.sense_ = ObjSense::kMinimize;
    milp.lp_.col_cost_ = ones;
    milp.lp_.col_lower_ = zeros;
    milp.lp_.col_upper_ = ones;
    milp.lp_.row_lower_ = ones;
    milp.lp_.row_upper_ = upper;
    milp.lp_.a_matrix_.format_ = MatrixFormat::kColwise;


    HighsStatus return_status;
  
    // Pass the model to HiGHS
    return_status = milp.passModel(model);
    assert(return_status==HighsStatus::kOk);
  
    // Get a const reference to the LP data in HiGHS
    const HighsLp& lp = milp.getLp();
  
    // Solve the model
    return_status = milp.run();
    assert(return_status==HighsStatus::kOk);
  
    // Get the model status
    const HighsModelStatus& model_status = milp.getModelStatus();
    assert(model_status==HighsModelStatus::kOptimal);
}
