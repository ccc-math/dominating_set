#add_subdirectory(greedy)

enable_testing()
include(GoogleTest)


add_executable(data_types_test)
add_executable(algo_test)

target_sources(data_types_test PRIVATE
	data_types_test.cpp)
target_sources(algo_test PRIVATE
	algo_test.cpp)

target_link_libraries(data_types_test 
	data_types
	GTest::gtest_main)
target_link_libraries(algo_test 
	data_types
	greedy
	genetic
	milp
	cp_sat
	GTest::gtest_main)


gtest_discover_tests(data_types_test algo_test
WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})


