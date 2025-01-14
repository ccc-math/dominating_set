#ifndef OUTPUT_H
#define OUTPUT_H

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <algorithm>
#include <data_types/graph.hpp>


class Output{
    private:
    int size;
    std::vector<int> dom;
    double runtime;
    public:
    Output();
    int get_size();
    void to_file();
    void add(int e);
    void set_runtime(double time);
    double get_runtime();
    std::vector<int> get_set();    
    bool is_in_set(const int& e);
    void to_csv(std::string filepath,std::string instance,std::string algo, std::string isdom);
    bool isDominatingSet(const Graph &G);
};

#endif