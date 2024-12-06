# Enable FetchContent.
include(FetchContent)

# Enable ExternalProject
include(ExternalProject)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)
    
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF)
FetchContent_MakeAvailable(googletest)

# Fetch Highs.
set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(
    highs
    URL https://github.com/ERGO-Code/HiGHS/archive/refs/tags/v1.7.2.zip
    EXCLUDE_FROM_ALL)
FetchContent_MakeAvailable(highs)

# Fetch Boost
include(FetchContent)
FetchContent_Declare(
    Boost
    URL https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.tar.xz
    EXCLUDE_FROM_ALL)
FetchContent_MakeAvailable(Boost)


# Based on https://github.com/fontanf/mathoptsolverscmake/blob/main/extern/CMakeLists.txt
# Errors to fix when using "cmake .." in the /build rep.

