cmake_minimum_required(VERSION 3.16)
project(sorting_visualizer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE C_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(${PROJECT_NAME} ${C_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    LTEngine)

add_dependencies(${PROJECT_NAME}
    LTEngine)
