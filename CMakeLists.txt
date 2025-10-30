cmake_minimum_required(VERSION 3.10)
project(Game_of_Life LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Автоопределение типа сборки ---
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Тип сборки" FORCE)
endif()

# --- Оптимизация для Release ---
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-O3)
else()
    add_compile_options(-g -O0)
endif()

# --- Исходники ---
file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# --- Исполняемый файл ---
add_executable(Game_of_Life
    "${CMAKE_CURRENT_SOURCE_DIR}/Game_of_Life.cpp"
    ${SRC_FILES}
)

# --- Заголовки ---
target_include_directories(Game_of_Life PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# --- .exe в корень проекта ---
set_target_properties(Game_of_Life PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}"
)

# --- Статическая линковка (MinGW) ---
if(MINGW)
    target_link_options(Game_of_Life PRIVATE -static -static-libgcc -static-libstdc++)
endif()