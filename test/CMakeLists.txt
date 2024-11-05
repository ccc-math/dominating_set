#add_subdirectory(greedy)

enable_testing()
include(GoogleTest)


add_executable(graph_test)
target_sources(graph_test PRIVATE
	graph_test.cpp)
target_link_libraries(graph_test 
	graph
	GTest::gtest_main)


gtest_discover_tests(graph_test 
WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
