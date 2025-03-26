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

option(LTENGINE_DEV_BUILD "Build LTEngine with dev features" OFF)

# Components
set(POSSIBLE_COMPONENTS
    LTENGINE_COMPONENT_ENGINE_CORE 
    LTENGINE_COMPONENT_C_API 
    LTENGINE_COMPONENT_GLFW 
    LTENGINE_COMPONENT_SDL
    LTENGINE_COMPONENT_PHYSICS_BOX2D 
    LTENGINE_COMPONENT_RENDERER_SOFTWARE 
    LTENGINE_COMPONENT_RENDERER_OPENGL
    LTENGINE_COMPONENT_RENDERER_VULKAN
    LTENGINE_COMPONENT_AUDIO_SOLOUD
)

option(LTENGINE_COMPONENT_ENGINE_CORE "The engine core" ON)
option(LTENGINE_COMPONENT_C_API "The C API, compatibility with bindings and C" ON)
option(LTENGINE_COMPONENT_GLFW "The GLFW windowing system" ON)
option(LTENGINE_COMPONENT_SDL "The SDL windowing and rendering system" OFF)

option(LTENGINE_COMPONENT_PHYSICS_BOX2D "The Box2D physics system" ON)

option(LTENGINE_COMPONENT_RENDERER_SOFTWARE "The software renderer" ON)
option(LTENGINE_COMPONENT_RENDERER_OPENGL "The OpenGL renderer" ON)
option(LTENGINE_COMPONENT_RENDERER_VULKAN "The Vulkan renderer" ON)

option(LTENGINE_COMPONENT_AUDIO_SOLOUD "The SoLoud audio engine" ON)


file(GLOB_RECURSE C_SOURCE_FILES CONFIGURE_DEPENDS 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
file(GLOB_RECURSE CXX_SOURCE_FILES CONFIGURE_DEPENDS 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)


# Library
if (NOT TARGET ${PROJECT_NAME})
    set(BUILD_STATIC ON)
    if (BUILD_SHARED_LIBS AND NOT LTENGINE_BUILD_STATIC AND NOT LTENGINE_BUILD_STATIC_CMAKE_IGNORE)
        message(STATUS "LTEngine: BUILD_SHARED_LIBS overrided LTENGINE_BUILD_STATIC to OFF")
        set(BUILD_STATIC OFF)
    elseif (LTENGINE_BUILD_STATIC)
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
        target_compile_definitions(${PROJECT_NAME} PUBLIC LTENGINE_SHARED)
    endif()

    if (LTENGINE_DEV_BUILD)
        target_compile_definitions(${PROJECT_NAME} PUBLIC LTENGINE_DEV_BUILD)
    endif()

    target_compile_definitions(${PROJECT_NAME} PUBLIC LTENGINE_VERSION_MAJOR=${CMAKE_PROJECT_VERSION_MAJOR})
    target_compile_definitions(${PROJECT_NAME} PUBLIC LTENGINE_VERSION_MINOR=${CMAKE_PROJECT_VERSION_MINOR})
    target_compile_definitions(${PROJECT_NAME} PUBLIC LTENGINE_VERSION_PATCH=${CMAKE_PROJECT_VERSION_PATCH})

    add_subdirectory(thirdparty/embed)
    b_embed(${PROJECT_NAME} resources/opengl/default_shader.vs)
    b_embed(${PROJECT_NAME} resources/opengl/default_shader.fs)
    b_embed(${PROJECT_NAME} resources/opengl/default_shader_texture.fs)
endif()

if (CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PUBLIC -fPIC)
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
