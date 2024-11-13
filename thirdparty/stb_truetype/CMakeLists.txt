project(stb_truetype LANGUAGES C)

add_library(${PROJECT_NAME} main.c)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
