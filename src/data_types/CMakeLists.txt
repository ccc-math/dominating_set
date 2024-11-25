add_library(data_types)
target_sources(data_types PRIVATE
    graph.cpp
    binaryHeap.cpp
    buckets.cpp)
target_include_directories(data_types PUBLIC 
	${PROJECT_SOURCE_DIR}/include)



