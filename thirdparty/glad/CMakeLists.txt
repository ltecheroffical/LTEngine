cmake_minimum_required(VERSION 3.16)
project(glad VERSION 3.3 LANGUAGES C)

add_library(${PROJECT_NAME} src/glad.c)

target_include_directories(${PROJECT_NAME} PUBLIC include/)
