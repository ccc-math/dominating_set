cmake_minimum_required(VERSION 3.30.1)

project(dom_set LANGUAGES CXX)


# Require C++14.
set(CMAKE_CXX_STANDARD 14)

cmake_policy(SET CMP0135 NEW)
set(DATA_PATH ${PROJECT_SOURCE_DIR}/data)
add_compile_definitions(dom_set PRIVATE "DATA_PATH=\"${DATA_PATH}\"")

# Enable output of compile commands during generation.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# Add sub-directories.
add_subdirectory(src)
add_subdirectory(extern)
add_subdirectory(test)

