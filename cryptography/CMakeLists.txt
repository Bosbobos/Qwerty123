cmake_minimum_required(VERSION 3.28)
project(cryptography)

set(CMAKE_CXX_STANDARD 23)

#include_directories(.)

#add_executable(crypto
#        crypto.cpp)
add_library(cryptography SHARED cryptography.cpp
        CryptographyManager.cpp)
