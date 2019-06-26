cmake_minimum_required(VERSION 3.13)
project(Assemble)

set(CMAKE_CXX_STANDARD 17)

# get sfml
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window audio network system)

file(GLOB_RECURSE sources "src/*.cpp")

# executable properties
add_executable(Assemble ${sources})
target_compile_options(Assemble PUBLIC -Wall)
target_include_directories(Assemble PUBLIC "include/")
target_link_libraries(Assemble sfml-graphics sfml-window sfml-audio sfml-network sfml-system)