cmake_minimum_required(VERSION 3.15)
project(psp VERSION 0.1.0 LANGUAGES CXX)

# set C++ Version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add libs
set(LIB_SOURCES
    src/symmetrical_components.cpp
    src/network_model.cpp
    src/short_circuit.cpp
    src/overcurrent_relay.cpp
)

add_library(psp STATIC ${LIB_SOURCES})

# add include directory
target_include_directories(psp PUBLIC include)

# application
add_executable(psp_demo app/main.cpp)
target_link_libraries(psp_demo PRIVATE psp)

# test framework
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)

if(MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()


FetchContent_MakeAvailable(googletest)

enable_testing()

set(TEST_SOURCES
    tests/test_symmetrical_components.cpp
    tests/test_network_model.cpp
    tests/test_short_circuit.cpp
    tests/test_overcurrent_relay.cpp
)

add_executable(psp_tests ${TEST_SOURCES})

target_link_libraries(psp_tests PRIVATE psp gtest_main)

include(GoogleTest)
gtest_discover_tests(psp_tests)