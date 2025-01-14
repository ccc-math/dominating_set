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