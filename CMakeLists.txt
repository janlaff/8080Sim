cmake_minimum_required(VERSION 3.15)
project(8080Sim)

set(CMAKE_CXX_STANDARD 17)

set(
        SOURCE_FILES
        Cpu.cpp
        main.cpp
)

add_executable(8080Sim ${SOURCE_FILES})