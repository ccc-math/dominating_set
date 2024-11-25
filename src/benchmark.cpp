#include "Graph/graph.hpp"
#include "Algo/greedy.hpp"

#include <chrono>
using namespace std::chrono;

int main(int argv, char* argc[]){


    td::string root_path=ROOT;
 
    // This structure would distinguish a file from a
    // directory
    struct stat sb;
    std::cout << root_path+"data"<<std::endl;
 
    //Loop on all items of directory
    for (const auto& entry : fs::directory_iterator(root_path+"data/pace_2016_instances/hidden")) {
 
        // Converting the path to const char * 
        std::filesystem::path outfilename = entry.path();
        std::string outfilename_str = outfilename.string();
        const char* path = outfilename_str.c_str();
 
        // Testing correction of path
        if (stat(path, &sb) == 0 && !(sb.st_mode & S_IFDIR)){
            std ::cout << path << std::endl;
            // Chrono Start
            time_point start = high_resolution_clock::now();

            // COmputations
    
            // Chrono End
            time_point stop = high_resolution_clock::now();
            //Duration Of Chrono
            duration duration = duration_cast<microseconds>(stop - start);}

        /*set(DATA_PATH ${PROJECT_SOURCE_DIR}/data)
add_compile_definitions(dom_set PRIVATE "DATA_PATH=\"${DATA_PATH}\"")

set(ROOT ${PROJECT_SOURCE_DIR}/)
add_compile_definitions(dom_set PRIVATE "ROOT=\"${ROOT}\"")*/
    }

    return 1;
    
}