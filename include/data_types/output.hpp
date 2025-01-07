#ifndef OUTPUT_H
#define OUTPUT_H

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <algorithm>


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
};

#endif