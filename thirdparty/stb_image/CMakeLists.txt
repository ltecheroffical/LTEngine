cmake_minimum_required(VERSION 3.16)
project(stb_image VERSION 0.1.0 LANGUAGES C)

if (NOT TARGET ${PROJECT_NAME})
    add_library(${PROJECT_NAME} src/stb_image.c)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include)
