cmake_minimum_required(VERSION 3.10)
project(Game_of_Life LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Исходники и заголовки
file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(Game_of_Life
    "${CMAKE_CURRENT_SOURCE_DIR}/Game_of_Life.cpp"
    ${SRC_FILES}
)

target_include_directories(Game_of_Life PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# exe в корне проекта (там где Game_of_Life.cpp)
set_target_properties(Game_of_Life PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)
