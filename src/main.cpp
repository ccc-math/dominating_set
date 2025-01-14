#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "data_types/graph.hpp"
#include "Algo/greedy.hpp"
#include "Algo/genetic.hpp"
#include "Algo/milp.hpp"
#include "Algo/cp_sat.hpp"

#include <boost/program_options.hpp>

namespace po = boost::program_options;


Output run(
        const Graph& instance,
        const po::variables_map& vm)
{

    // Run algorithm.
    std::string algorithm = vm["algorithm"].as<std::string>();
    if (algorithm == "greedy") {
        std::string type = vm["type"].as<std::string>();
        if(type == "heap"){
            return smarterGreedyHeapV2(instance);
        }
        else if(type == "bucket"){
            //return smarterBucketsOfBuckets(instance);
        }
    }
    if (algorithm == "genetic") {
        return large_scale_search(instance,1000);
    }

    if(algorithm == "milp"){
        const double time_limit = 10;
        return milp(instance, time_limit);
    }
    if(algorithm == "sat" || algorithm == "cp_sat"){
        const double time_limit = 10;
        return cp_sat(instance, time_limit);
    }
    

 else {
        throw std::invalid_argument(
                "Unknown algorithm \"" + algorithm + "\".");
    }
}


int main(int argc, char *argv[])
{
    // Parse program options
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "produce help message")
        ("algorithm,a", po::value<std::string>()->required(), "set algorithm (required)")
        ("type,y",po::value<std::string>(),"set algorithm type for greedys")
        ("input,i", po::value<std::string>()->required(), "set input file (required)")
        ("output,o",po::value<std::string>(),"set output path")
        ;
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    if (vm.count("help")) {
        std::cout << desc << std::endl;;
        return 1;
    }
    try {
        po::notify(vm);
    } catch (const po::required_option& e) {
        std::cout << desc << std::endl;;
        return 1;
    }

    // Build instance.
    const Graph instance(
            vm["input"].as<std::string>());
    // Run.
    Output output = run(instance, vm);
    
    // Export the solution in a csv_file.
    output.exporter(vm);

    std::cout << "size of the solution : " << output.get_size()<<std::endl;
    std::cout << "Runtime of the algorithm : " << output.get_runtime() << " seconds." << std::endl;

    

    return 0;
}
