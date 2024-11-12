cmake_minimum_required(VERSION 3.10)
project(window_not_needed_example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE C_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(window_not_needed_example ${C_SOURCES})

target_link_libraries(window_not_needed_example PRIVATE
    LTEngine)

add_dependencies(window_not_needed_example
    LTEngine)
