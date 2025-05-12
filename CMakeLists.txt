cmake_minimum_required(VERSION 3.16)
project(LTCore VERSION 1.0.0 LANGUAGES C CXX ASM)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


option(LTCORE_BUILD_STATIC "Build LTCore as a static library" ON)
option(LTCORE_BUILD_STATIC_CMAKE_IGNORE "Do not override if BUILD_SHARED_LIBS is set" OFF)

option(LTCORE_BUILD_EXAMPLES "Build LTCore examples" ON)
option(LTCORE_BUILD_TESTS "Build LTCore tests" ON)
option(LTCORE_BUILD_DOCS "Build LTCore documentation" ON)

option(LTCORE_DEV_BUILD "Build LTCore with dev features" OFF)

# Components
set(POSSIBLE_COMPONENTS
    LTCORE_COMPONENT_ENGINE_CORE 
    LTCORE_COMPONENT_C_API 
    LTCORE_COMPONENT_PHYSICS_BOX2D 
)

option(LTCORE_COMPONENT_ENGINE_CORE "The engine core" ON)
option(LTCORE_COMPONENT_C_API "The C API, compatibility with bindings and C" ON)

option(LTCORE_COMPONENT_PHYSICS_BOX2D "The Box2D physics system" ON)


file(GLOB_RECURSE C_SOURCE_FILES CONFIGURE_DEPENDS 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
file(GLOB_RECURSE CXX_SOURCE_FILES CONFIGURE_DEPENDS 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)


# Library
if (NOT TARGET ${PROJECT_NAME})
    set(BUILD_STATIC ON)
    if (BUILD_SHARED_LIBS AND NOT LTCORE_BUILD_STATIC AND NOT LTCORE_BUILD_STATIC_CMAKE_IGNORE)
        message(STATUS "LTCore: BUILD_SHARED_LIBS overrided LTCORE_BUILD_STATIC to OFF")
        set(BUILD_STATIC OFF)
    elseif (LTCORE_BUILD_STATIC)
        set(BUILD_STATIC ON)
    else()
        set(BUILD_STATIC OFF)
    endif()

    foreach (OPTION_NAME ${POSSIBLE_COMPONENTS})
        if (${OPTION_NAME})
            add_compile_definitions(${OPTION_NAME})
        endif()
    endforeach()

    
    if (BUILD_STATIC)
        add_library(${PROJECT_NAME} STATIC ${C_SOURCE_FILES} ${CXX_SOURCE_FILES} ${ASM_SOURCE_FILES})
    else()
        add_library(${PROJECT_NAME} SHARED ${C_SOURCE_FILES} ${CXX_SOURCE_FILES} ${ASM_SOURCE_FILES})
        target_compile_definitions(${PROJECT_NAME} PUBLIC LTCORE_SHARED)
    endif()
    
    set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

    if (LTCORE_DEV_BUILD)
        target_compile_definitions(${PROJECT_NAME} PUBLIC LTCORE_DEV_BUILD)
    endif()

    target_compile_definitions(${PROJECT_NAME} PUBLIC LTCORE_VERSION_MAJOR=${CMAKE_PROJECT_VERSION_MAJOR})
    target_compile_definitions(${PROJECT_NAME} PUBLIC LTCORE_VERSION_MINOR=${CMAKE_PROJECT_VERSION_MINOR})
    target_compile_definitions(${PROJECT_NAME} PUBLIC LTCORE_VERSION_PATCH=${CMAKE_PROJECT_VERSION_PATCH})

    if (NOT LTCORE_DEV_BUILD)
        set(B_PRODUCTION_MODE ON)
    endif()
    add_subdirectory(thirdparty/embed)
endif()


# Thirdparty
add_subdirectory(thirdparty)

# Docs
if (LTCORE_BUILD_DOCS)
    add_subdirectory(doc)
endif()

# Tests
if (LTCORE_BUILD_TESTS)
    message(STATUS "LTCore: Tests are enabled")
    enable_testing()
    add_subdirectory(tests)
endif()

# Examples
if (LTCORE_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Dev
if (LTCORE_DEV_BUILD)
    add_subdirectory(test_app)
endif()


# Linking
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include)
