cmake_minimum_required(VERSION 3.8)
project(node_cgns)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/Base.cc
        src/Base.h
        src/cgns.cc
        src/Doc.cc
        src/Doc.h
        src/helper.cc
        src/helper.h
        src/v8Helper.h
        src/Zone.cc
        src/Zone.h
        src/Grid.cc
        src/Coord.cc
        src/Solution.cc)

add_executable(node_cgns ${SOURCE_FILES})