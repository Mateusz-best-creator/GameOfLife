set(include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Add human library
add_library(human STATIC human.cpp)
target_include_directories(human PUBLIC ${include_directories})

# Add animal and plant classes
add_library(animal STATIC animal.cpp)
target_include_directories(animal PUBLIC ${include_directories})
# link animal with human
target_link_libraries(animal PUBLIC human)

add_library(plant STATIC plant.cpp)
target_include_directories(plant PUBLIC ${include_directories})

add_library(organism STATIC organism.cpp)
target_include_directories(organism PUBLIC ${include_directories})

# Link organism with animal and plant classes
target_link_libraries(organism PUBLIC plant animal)

add_library(world STATIC world.cpp)
target_include_directories(world PUBLIC ${include_directories})
target_link_libraries(world PUBLIC organism)