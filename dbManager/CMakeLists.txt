cmake_minimum_required(VERSION 3.27)
project(PostgresCRUDLibrary)

set(CMAKE_CXX_STANDARD 14)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

include_directories(${PQXX_INCLUDE_DIRS})
link_directories(${PQXX_LIBRARY_DIRS})

add_library(dbContext SHARED dbContext.cpp)

target_link_libraries(dbContext ${PQXX_LIBRARIES})
