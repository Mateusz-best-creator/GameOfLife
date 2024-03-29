set(include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Add human library
add_library(libhuman STATIC human.cpp)
target_include_directories(libhuman PUBLIC ${include_directories})

# Add animal and plant classes
add_library(libanimal STATIC animal.cpp)
target_include_directories(libanimal PUBLIC ${include_directories})
# link animal with human
target_link_libraries(libanimal PUBLIC libhuman)

add_library(libplant STATIC plant.cpp)
target_include_directories(libplant PUBLIC ${include_directories})

add_library(liborganism STATIC organism.cpp)
target_include_directories(liborganism PUBLIC ${include_directories})

# Link organism with animal and plant classes
target_link_libraries(liborganism PUBLIC libplant libanimal)

add_library(libworld STATIC world.cpp)
target_include_directories(libworld PUBLIC ${include_directories})
target_link_libraries(libworld PUBLIC liborganism)