cmake_minimum_required(VERSION 3.27)
project(Qwerty123)

set(CMAKE_CXX_STANDARD 23)

pkg_check_modules(PQXX REQUIRED libpqxx)

include_directories(${PQXX_INCLUDE_DIRS})
link_directories(${PQXX_LIBRARY_DIRS})

# Define the library target
add_library(dbManager SHARED dbManager/crud.cpp)

# Link the library with libpqxx
target_link_libraries(dbManager ${PQXX_LIBRARIES})

# Define the main executable
add_executable(Qwerty123 main.cpp)

# Link the main executable with the library
target_link_libraries(Qwerty123 dbManager)