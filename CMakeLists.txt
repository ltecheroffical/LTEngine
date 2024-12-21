cmake_minimum_required(VERSION 3.16)
project(LTEngine VERSION 1.0.0 LANGUAGES C CXX ASM)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


option(LTENGINE_BUILD_STATIC "Build LTEngine as a static library" ON)
option(LTENGINE_BUILD_STATIC_CMAKE_IGNORE "Do not override if BUILD_SHARED_LIBS is set" OFF)

option(LTENGINE_BUILD_EXAMPLES "Build LTEngine examples" ON)
option(LTENGINE_BUILD_TESTS "Build LTEngine tests" ON)
option(LTENGINE_BUILD_DOCS "Build LTEngine documentation" ON)

option(LTENGINE_BUILD_WITH_SDL "Build SDL into LTEngine" OFF)
option(LTENGINE_DISABLE_GLFW "Disable GLFW building and linking (useful for github actions due to the headless mode)" OFF)


file(GLOB_RECURSE C_SOURCE_FILES CONFIGURE_DEPENDS 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
file(GLOB_RECURSE CXX_SOURCE_FILES CONFIGURE_DEPENDS 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)


# Library
if (NOT TARGET ${PROJECT_NAME})
    set(BUILD_STATIC LTENGINE_BUILD_STATIC)

    if (BUILD_SHARED_LIBS AND NOT BUILD_STATIC AND NOT LTENGINE_BUILD_STATIC_CMAKE_IGNORE)
        message(STATUS "LTEngine: BUILD_SHARED_LIBS overrided LTENGINE_BUILD_STATIC to OFF")
        set(BUILD_STATIC OFF)
    endif()

    if (BUILD_STATIC)
        add_library(${PROJECT_NAME} STATIC ${C_SOURCE_FILES} ${CXX_SOURCE_FILES} ${ASM_SOURCE_FILES})
    else()
        add_library(${PROJECT_NAME} SHARED ${C_SOURCE_FILES} ${CXX_SOURCE_FILES} ${ASM_SOURCE_FILES})
        target_compile_definitions(${PROJECT_NAME} PUBLIC LTENGINE_SHARED)
    endif()

    if (LTENGINE_DISABLE_GLFW)
        target_compile_definitions(${PROJECT_NAME} PUBLIC LTENGINE_DISABLE_GLFW)
    endif()

    if (LTENGINE_BUILD_WITH_SDL)
        target_compile_definitions(${PROJECT_NAME} PUBLIC LTENGINE_SDL_ENABLE)
    endif()
endif()

# Thirdparty
add_subdirectory(thirdparty)

# Docs
if (LTENGINE_BUILD_DOCS)
    add_subdirectory(doc)
endif()

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
