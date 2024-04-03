cmake_minimum_required(VERSION 3.9)

project(GameOfLife
        LANGUAGES CXX
        DESCRIPTION "Game of life written in C++ language"
        VERSION 0.0.1)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)

# Find SDL2 library
find_package(SDL2 REQUIRED)
# Include SDL2 headers
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(GameOfLife src/main.cpp )
target_link_libraries(GameOfLife PRIVATE world ${SDL2_LIBRARIES})

# Add compiler flags
target_compile_options(GameOfLife PRIVATE -Wall -Wextra)