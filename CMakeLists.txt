cmake_minimum_required(VERSION 3.24.2)
project(jada)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(jada main.cpp
        src/index/UniqueIndex.cpp)
