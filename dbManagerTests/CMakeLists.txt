cmake_minimum_required(VERSION 3.27)
project(dbManagerTests)

set(CMAKE_CXX_STANDARD 23)

# Use find_package to locate libpqxx and make it available for the project
find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

# Locate and include Google Test
find_package(GTest REQUIRED)

# Add an executable target for the test suite
add_executable(dbManagerTests CrudTest.cpp dbManagerTest.cpp)

# Link the test executable with the library being tested and Google Test
add_subdirectory(../dbManager dbManager)
target_link_libraries(dbManagerTests PRIVATE dbManager GTest::GTest GTest::Main)

# Include directories for the library and Google Test
target_include_directories(dbManagerTests PRIVATE ${PQXX_INCLUDE_DIRS})
target_link_libraries(dbManagerTests PRIVATE ${PQXX_LIBRARIES})
target_include_directories(dbManagerTests PRIVATE ${GTEST_INCLUDE_DIRS})

# Copy config file to the build directory
configure_file(${CMAKE_SOURCE_DIR}/config.txt ${CMAKE_BINARY_DIR}/config.txt COPYONLY)
