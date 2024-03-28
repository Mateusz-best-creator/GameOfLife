set(include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../include)

add_library(liborganism STATIC organism.cpp)
target_include_directories(liborganism PUBLIC ${include_directories})

add_library(libworld STATIC world.cpp)
target_include_directories(libworld PUBLIC ${include_directories})
target_link_libraries(libworld PUBLIC liborganism)