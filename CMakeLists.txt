cmake_minimum_required(VERSION 3.16)
project(LTEngine VERSION 0.1.0 LANGUAGES C CXX ASM)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(LTENGINE_BUILD_EXAMPLES "Build LTEngine examples" ON)
option(LTENGINE_BUILD_TESTS "Build LTEngine tests" ON)

option(LTENGINE_BUILD_WITH_SDL "Build SDL into LTEngine" OFF)


file(GLOB_RECURSE C_SOURCE_FILES CONFIGURE_DEPENDS 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
file(GLOB_RECURSE CXX_SOURCE_FILES CONFIGURE_DEPENDS 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Library
if (NOT TARGET ${PROJECT_NAME})
    add_library(${PROJECT_NAME} ${C_SOURCE_FILES} ${CXX_SOURCE_FILES} ${ASM_SOURCE_FILES})
endif()


if (LTENGINE_BUILD_WITH_SDL)
    target_compile_definitions(${PROJECT_NAME} PUBLIC LTENGINE_SDL_ENABLE)
endif()

# Thirdparty
add_subdirectory(thirdparty)

# Tests
if (LTENGINE_BUILD_TESTS)
    message(STATUS "LTEngine: Tests are enabled")
    enable_testing()
    add_subdirectory(tests)
endif()

# Examples
if (LTENGINE_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()


# Linking
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include)
