cmake_minimum_required(VERSION 3.28)
project(Configs)

set(CMAKE_CXX_STANDARD 23)

add_library(Configs SHARED ConfigManager.cpp)

# Copy config file to the build directory
configure_file(${CMAKE_SOURCE_DIR}/../Configs/DbConf.txt ${CMAKE_BINARY_DIR}/DbConf.txt COPYONLY)
