project(glad LANGUAGES C)

add_library(glad src/glad.c)

if (CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PUBLIC -fPIC)
endif()

target_include_directories(glad PUBLIC include)
