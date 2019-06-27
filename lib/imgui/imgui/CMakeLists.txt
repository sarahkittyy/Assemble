# CMakeLists written by sarahkitty <sarahohlin1@gmail.com>
cmake_minimum_required(VERSION 3.13)
project(ImGUI)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE sources "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(imgui ${sources})
target_include_directories(imgui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/")