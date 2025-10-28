cmake_minimum_required(VERSION 3.10)
project(GameOfLife LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Все .cpp из src/
file(GLOB SOURCES "src/*.cpp")

# Исполняемый файл
add_executable(GameOfLife ${SOURCES})

# Заголовки
target_include_directories(GameOfLife PRIVATE include)

# ВЫХОД В src/ (а не в build/)
set_target_properties(GameOfLife PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/src
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/src
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/src
)