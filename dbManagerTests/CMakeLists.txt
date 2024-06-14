cmake_minimum_required(VERSION 3.27)
project(dbManagerTests)

set(CMAKE_CXX_STANDARD 23)

# Use find_package to locate libpqxx and make it available for the project
find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

# Locate and include Google Test
find_package(GTest REQUIRED)

# Add the library targets (assuming they are part of this project)
# You should ensure these libraries are built before linking them
add_subdirectory(../dbManager ${CMAKE_BINARY_DIR}/dbManager)
add_subdirectory(../Configs ${CMAKE_BINARY_DIR}/Configs)

# Add an executable target for the test suite
add_executable(dbManagerTests CrudTest.cpp dbManagerTest.cpp AuthManagerTest.cpp)

# Include directories for the library and Google Test
target_include_directories(dbManagerTests PRIVATE ../dbManager ../Configs ${PQXX_INCLUDE_DIRS} ${GTEST_INCLUDE_DIRS})

# Link the test executable with the library being tested and Google Test
target_link_libraries(dbManagerTests PRIVATE dbManager Configs ${PQXX_LIBRARIES} GTest::GTest GTest::Main)
