#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "data_types/graph.hpp"
#include "data_types/output.hpp"
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
    double time_limit = vm["time-limit"].as<double>();
    // Run algorithm.
    std::string algorithm = vm["algorithm"].as<std::string>();
    if(algorithm == "heap"){
        return smarterGreedyHeapV2(instance);
    }
    if(algorithm == "bucket"){
        std::vector<int> empty = {};
        return smarterBucketsOfBucketsV2(instance,empty);
    }
    
    if (algorithm == "genetic") {
        return large_scale_search(instance,time_limit);
    }
    if (algorithm == "wgenetic"){
        return large_scale_search_with_weights(instance,time_limit, 0.99, 0.2, 10, 2);

    }

    if(algorithm == "milp"){
        return milp(instance, time_limit);
    }
    if(algorithm == "sat" || algorithm == "cp_sat"){
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
        ("input,i", po::value<std::string>()->required(), "set input file (required)")
        ("output,o",po::value<std::string>(),"set output path")
        ("time-limit,t",po::value<double>()->default_value(30.0),"set maximum computation time")
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
    std::string isdom = "false";
    if(vm.count("output")){
        if(output.isDominatingSet(instance)){
            isdom = "true" ;
        }
        output.to_csv(vm["output"].as<std::string>(),vm["input"].as<std::string>(),vm["algorithm"].as<std::string>(),isdom);
    }

    return 0;
}
