add_library(greedy)

add_library(genetic)

target_sources(greedy PRIVATE
	greedy.cpp)

target_sources(genetic PRIVATE
	genetic.cpp)

target_link_libraries(greedy PUBLIC
	graph)

target_link_libraries(genetic PUBLIC
	graph)

target_include_directories(greedy PUBLIC
	$(PROJECT_SOURCE_DIR)/include)

target_include_directories(genetic PUBLIC
	$(PROJECT_SOURCE_DIR)/include)





