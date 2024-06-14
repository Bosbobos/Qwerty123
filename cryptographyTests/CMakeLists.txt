cmake_minimum_required(VERSION 3.27)
project(cryptographyTests)

set(CMAKE_CXX_STANDARD 23)

# Locate and include Google Test
find_package(GTest REQUIRED)

# Add an executable target for the test suite
add_executable(cryptographyTests CryptographyManagerTests.cpp)

# Link the test executable with the library being tested and Google Test
add_subdirectory(../cryptography cryptography)
target_link_libraries(cryptographyTests PRIVATE cryptography GTest::GTest GTest::Main)

# Set output directory to avoid conflicts with directory names
set_target_properties(cryptographyTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

target_include_directories(cryptographyTests PRIVATE ${GTEST_INCLUDE_DIRS})
