#ifndef OUTPUT_H
#define OUTPUT_H

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <algorithm>
#include <boost/program_options.hpp>



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
    void set_output(std::vector<int> vec);
    std::vector<int> get_set();    
    bool is_in_set(const int& e);
    void exporter(const boost::program_options::variables_map& vm);
    void to_file(std::string filepath,std::string instance,std::string algo, std::string isdom);
};
#endif