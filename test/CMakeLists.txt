#add_subdirectory(greedy)

enable_testing()
include(GoogleTest)


add_executable(graph_test)
add_executable(greedy_test)

target_sources(graph_test PRIVATE
	graph_test.cpp)
target_sources(greedy_test PRIVATE
	greedy_test.cpp)

target_link_libraries(graph_test 
	data_types
	GTest::gtest_main)
target_link_libraries(greedy_test 
	data_types
	greedy
	GTest::gtest_main)


gtest_discover_tests(graph_test greedy_test 
WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
