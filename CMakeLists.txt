cmake_minimum_required(VERSION 3.17)
project(project)

set(CMAKE_CXX_STANDARD 14)

add_executable(project main.cpp Algorithm.cpp Algorithm.h AlgorithmInfAb.cpp AlgorithmInfAb.h Naive.cpp Naive.h ReadFile.cpp ReadFile.h CreateData.cpp CreateData.h)