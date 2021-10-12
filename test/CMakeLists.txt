# Setup project
cmake_minimum_required(VERSION 3.12.2)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MACOSX_RPATH 1)

project(robot_dog_tests)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_compile_definitions(TESTING)

include(CTest)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src)
include_directories(${SRC_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(hal)
add_subdirectory(input_devices)
add_subdirectory(mathmatics)
add_subdirectory(robot)

add_library(unittests STATIC main.cpp)

target_link_libraries(unittests PUBLIC CONAN_PKG::gtest)
