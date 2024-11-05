add_library(graph)
target_sources(graph PRIVATE
    graph.cpp)
target_include_directories(graph PUBLIC 
	${PROJECT_SOURCE_DIR}/include)



