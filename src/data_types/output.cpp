#include "data_types/output.hpp"


Output::Output(){
    size=0;
    dom=std::vector<int>({});
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

void Output::to_file(){

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

void Output::exporter(const boost::program_options::variables_map& vm) {
    /*
    * Add in csv file information about the algorithm in the following order :
    * - name instance
    * - size of the solution
    * - solution
    * - runtime of the algo
    * - ?
    */
    std::string instance_name = vm["input"].as<std::string>();
    std::string algo_name = vm["algorithm"].as<std::string>();
    std::ofstream file;
    file.open("../data/" + instance_name + "_" + algo_name + ".sol");
    file << instance_name << ";" << size << "; {";
    for (int i; i < size-1; i++) {
        file << std::to_string(dom[i]) + ", ";
    }
    file << std::to_string(dom[size - 1]) + "} ;" << runtime << ";" << "\n";
    file.close();
}
