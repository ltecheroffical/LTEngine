cmake_minimum_required(VERSION 3.16)

# Windowing
if (LTENGINE_COMPONENT_SDL)
    add_subdirectory(SDL) # Oof, this takes a while to compile
    target_link_libraries(${PROJECT_NAME} PUBLIC SDL3)
endif()

if (LTENGINE_COMPONENT_GLFW)
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

    add_subdirectory(glfw)
    target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
endif()

# GPU Graphics
add_subdirectory(glad)
if (LTENGINE_COMPONENT_RENDERER_LLGL)
    add_subdirectory(LLGL)
    target_link_libraries(${PROJECT_NAME} PUBLIC LLGL)
endif()

# Math
add_subdirectory(glm)

# Physics
if (LTENGINE_COMPONENT_PHYSICS_BOX2D)
    add_subdirectory(box2d)
    target_link_libraries(${PROJECT_NAME} PUBLIC box2d)
endif()

# Audio
if (LTENGINE_COMPONENT_AUDIO_SOLOUD)
    cmake_policy(SET CMP0175 OLD)
    add_subdirectory(soloud)
    target_link_libraries(${PROJECT_NAME} PUBLIC soloud)
endif()

# STB Utilites
add_subdirectory(stb_image)
add_subdirectory(stb_truetype)

# Linking
if (LTENGINE_BUILD_WITH_SDL)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC
    # GPU Graphics
    glad

    # Math
    glm::glm

    # STB Utilities
    stb_image
    stb_truetype
)
