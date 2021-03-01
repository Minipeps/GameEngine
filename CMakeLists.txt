cmake_minimum_required(VERSION 3.18)

project(EngineProject VERSION 0.0.1)

# Third Parties
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
# set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} third_party/packages/glfw)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} third_party/packages/SDL2)
# find_package(glfw3 3.3 REQUIRED)
find_package(SDL2 2.0.14 REQUIRED)
# add_subdirectory(third_parties)

# Engine Target
set(ENGINE_HEADER_DIR include)
file(GLOB ENGINE_SOURCES src/*.cpp)

add_library(Engine STATIC ${ENGINE_SOURCES} src/glad.c)
target_include_directories(Engine PUBLIC ${ENGINE_HEADER_DIR})

# Link third parties
target_include_directories(Engine PUBLIC ${SDL2_INCLUDE_DIR})
target_link_libraries(Engine PRIVATE ${SDL2_LIBRARIES})

##### Samples #####

add_subdirectory(samples)
