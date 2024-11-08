cmake_minimum_required(VERSION 3.10)
project(pong_example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE PONG_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(pong_example ${PONG_SOURCES})

target_link_libraries(pong_example PRIVATE
    LTEngine)

add_dependencies(pong_example
    LTEngine)
