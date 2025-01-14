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

void Output::set_output(std::vector<int> vec){
    dom = vec;
    size = vec.size();
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

void Output::to_file(std::string filepath,std::string instance,std::string algo, std::string isdom){

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
