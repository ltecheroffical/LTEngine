# Windowing
if (LTENGINE_BUILD_WITH_SDL)
    add_subdirectory(SDL) # Oof, this takes a while to compile
    add_library(SDL2 ALIAS SDL2-static)
endif()

add_subdirectory(glfw)

# GPU Graphics
add_subdirectory(glad)

# Physics
add_subdirectory(box2d)

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

target_link_libraries(${PROJECT_NAME} PUBLIC
    # Windowing
    glfw

    # GPU Graphics
    glad

    # Physics
    box2d

    # STB Utilities
    stb_image
    stb_truetype
)
