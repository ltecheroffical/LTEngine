cmake_minimum_required(VERSION 3.16)

# Windowing
if (LTENGINE_BUILD_WITH_SDL)
    add_subdirectory(SDL) # Oof, this takes a while to compile
    add_library(SDL2 ALIAS SDL2-static)
endif()

if (NOT LTENGINE_DISABLE_GLFW)
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

    add_subdirectory(glfw)
endif()

# GPU Graphics
add_subdirectory(glad)

# Math
add_subdirectory(glm)

# Physics
add_subdirectory(box2d)

# Audio
add_subdirectory(soloud)

# STB Utilites
add_subdirectory(stb_image)
add_subdirectory(stb_truetype)


# Linking
if (LTENGINE_BUILD_WITH_SDL)
    target_link_libraries(${PROJECT_NAME} PUBLIC
        # Windowing
        SDL2
    )
endif()

if (NOT LTENGINE_DISABLE_GLFW)
    target_link_libraries(${PROJECT_NAME} PUBLIC
        # Windowing
        glfw
    )
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC
    # GPU Graphics
    glad

    # Math
    glm::glm

    # Physics
    box2d

    # Audio
    soloud

    # STB Utilities
    stb_image
    stb_truetype
)
