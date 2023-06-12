cmake_minimum_required(VERSION 3.22)
project(fractalgraph)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(fractalgraph
        graph.cc
        main.cc Directed.hh Directed.cc)
