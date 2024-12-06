add_subdirectory(data_types)
add_subdirectory(Algo)



add_executable(dom_set_main)
target_sources(dom_set_main PRIVATE
    main.cpp)
target_link_libraries(dom_set_main PUBLIC
    data_types
    greedy
    genetic
    milp

    )


