add_library(greedy)

target_sources(greedy PRIVATE
	greedy.cpp)
target_link_libraries(greedy PUBLIC
	data_types)

target_include_directories(greedy PUBLIC
	${PROJECT_SOURCE_DIR}/include)


add_library(genetic)

target_sources(genetic PRIVATE
	genetic.cpp)

target_link_libraries(genetic PUBLIC
	data_types)

target_include_directories(genetic PUBLIC
	${PROJECT_SOURCE_DIR}/include)


add_library(milp)

target_sources(milp PRIVATE
	milp.cpp)

target_link_libraries(milp PUBLIC
	data_types
	highs)

target_include_directories(milp PUBLIC
	${PROJECT_SOURCE_DIR}/include)

add_library(cp_sat)
target_sources(cp_sat PRIVATE
    cp_sat.cpp)

target_link_libraries(cp_sat PUBLIC
    data_types
    DominatingSet_ortools)

target_include_directories(cp_sat PUBLIC
    ${PROJECT_SOURCE_DIR}/include)

