cmake_minimum_required(VERSION 3.27)
project(dbManager)

set(CMAKE_CXX_STANDARD 23)

# Use find_package to locate libpqxx and make it available for the project
find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

# Define the library target
add_library(dbManager SHARED dbManager.cpp PostgresCRUD.cpp
        authManager.cpp)

# Include directory for Entities
add_subdirectory(../Entities Entities)
target_include_directories(dbManager PUBLIC ../Entities)

# Link the library with libpqxx and Entities
target_include_directories(dbManager PRIVATE ${PQXX_INCLUDE_DIRS})
target_link_libraries(dbManager PUBLIC Entities)
target_link_libraries(dbManager PRIVATE ${PQXX_LIBRARIES})
