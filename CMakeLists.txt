cmake_minimum_required(VERSION 3.12)
project(QAPGeneticAlgorithm)

set(CMAKE_CXX_STANDARD 17)

add_executable(QAPGeneticAlgorithm main.cpp globals.h GA.h tours.h tours.cpp tourChroms.h tourChroms.cpp cityMapCoords.h cityMapCoords.cpp GA.cpp)