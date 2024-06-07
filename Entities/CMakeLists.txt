cmake_minimum_required(VERSION 3.27)
project(Entities)

set(CMAKE_CXX_STANDARD 23)

# Define the library target
add_library(Entities SHARED Record.cpp)
