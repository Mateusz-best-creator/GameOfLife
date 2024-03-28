cmake_minimum_required(VERSION 3.9)

project(GameOfLife
        LANGUAGES CXX
        DESCRIPTION "Game of life written in C++ language"
        VERSION 0.0.1)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#add_subdirectory(src)

add_executable(GameOfLife src/main.cpp )