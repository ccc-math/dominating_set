#include "data_types/output.hpp"


Output::Output(){
    size=0;
    dom=std::vector<int>({});
    runtime = 0;
}

int Output::get_size(){
    return size;
}

void Output::set_runtime(double t){
    runtime = t;
}

double Output::get_runtime(){
    return runtime;
}


void Output::add(int e){
    size++;
    dom.push_back(e);

}

std::vector<int> Output::get_set(){
    return dom;
}

bool Output::is_in_set(const int& e){
    auto it = std::find(dom.begin(),dom.end(),e);
    return(it!=dom.end());
}

void Output::to_csv(std::string filepath,std::string instance,std::string algo, std::string isdom){

    // Open the file in write mode
    std::ofstream file(filepath,std::ios::app);

    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
    }

    // Data to write (rows of CSV)

    std::vector<std::string> data = 
        {instance, algo, isdom, std::to_string(size),std::to_string(runtime)};

    // Write data to the file
    for (size_t i = 0; i < data.size(); ++i) {
        file << data[i];            // Write the data element
        if (i < data.size() - 1) {  // Add a comma if not the last element
            file << ",";
        }
    }
    file<<"\n";
    file.close();

}

bool Output::isDominatingSet(const Graph& G){
    std::vector<bool> isDominated = {};
    for(int i = 0; i < G.getNumVertices(); i++){
        isDominated.push_back(false);
    }
    for(int v : this->dom){

        for(int nei : G.getNeighbours(v)){
            
            isDominated[nei] = true;
        }
        isDominated[v] = true;
    }
    for(bool b : isDominated){
        if(!b){
            return false;
        }
    }
    return true;
}

