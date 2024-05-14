cmake_minimum_required(VERSION 3.10)
project(GameOfLife)

# Set C++ version
set(CMAKE_CXX_STANDARD 14)

# Add include directory
include_directories(include)

set(SOURCES
    src/main.cpp
    src/world.cpp
    src/organism.cpp
    src/animal.cpp
    src/human.cpp
    src/wolf.cpp
    src/sheep.cpp
    src/fox.cpp
    src/turtle.cpp
    src/antelope.cpp
    src/cyber_sheep.cpp
    src/plant.cpp
    src/grass.cpp
    src/sosnowsky_hogweed.cpp
)

# Find SDL2 package
find_package(SDL2 REQUIRED)

# Add executable target
add_executable(${PROJECT_NAME} ${SOURCES})

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

# Set compiler flags
if (CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
elseif (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
endif()
