add_library(greedy)

target_sources(greedy PRIVATE
	greedy.cpp)

target_link_libraries(greedy PUBLIC
	graph)

target_include_directories(greedy PUBLIC
	$(PROJECT_SOURCE_DIR)/include)





