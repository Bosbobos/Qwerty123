cmake_minimum_required(VERSION 3.27)
project(Qwerty123)

set(CMAKE_CXX_STANDARD 23)

# Use find_package to locate libpqxx and make it available for the project
find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

# Define the main executable
add_executable(Qwerty123 main.cpp)

# Link the main executable with the dbContext library
add_subdirectory(dbManager)
target_link_libraries(Qwerty123 dbContext)