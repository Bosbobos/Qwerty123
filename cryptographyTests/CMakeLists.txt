cmake_minimum_required(VERSION 3.27)
project(cryptographyTests)

set(CMAKE_CXX_STANDARD 23)


# Поиск и включение Google Test
find_package(GTest REQUIRED)

# Добавление исходных файлов библиотеки
add_library(cryptography STATIC ../cryptography/cryptography.cpp ../cryptography/CryptographyManager.cpp)

# Указание директорий для include
target_include_directories(cryptography PUBLIC ../cryptography)

# Добавление исполняемого файла для тестов
add_executable(cryptographyTests CryptographyManagerTests.cpp cryptographyTests.cpp)

# Линковка тестов с библиотекой и Google Test
target_link_libraries(cryptographyTests PRIVATE cryptography GTest::GTest GTest::Main)

# Установка выходной директории
set_target_properties(cryptographyTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Указание директорий для include для тестов
target_include_directories(cryptographyTests PRIVATE ${GTEST_INCLUDE_DIRS})