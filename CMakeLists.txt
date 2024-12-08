cmake_minimum_required(VERSION 3.29.2)

project(dom_set LANGUAGES CXX)

# Require C++17.
set(CMAKE_CXX_STANDARD 17)

cmake_policy(SET CMP0135 NEW)

# Enable output of compile commands during generation.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# Add sub-directories.
add_subdirectory(src)
add_subdirectory(extern)
add_subdirectory(test)

