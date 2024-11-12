# Rendering
add_subdirectory(stb_image)

# Windowing
if (LTENGINE_BUILD_WITH_SDL)
    add_subdirectory(SDL) # Oof, this takes a while to compile
endif()

# OpenGL/Windowing
add_subdirectory(glad)
add_subdirectory(glfw)

# Physics
add_subdirectory(box2d)

target_link_libraries(${PROJECT_NAME} PUBLIC
    # OpenGL/Windowing
    glfw
    glad

    # Physics
    box2d
)

if (LTENGINE_BUILD_WITH_SDL)
    if (NOT BUILD_SHARED_LIBS)
        add_library(SDL2 ALIAS SDL2-static)
    endif()

    target_link_libraries(${PROJECT_NAME} PUBLIC
        SDL2
    )
endif()


# Linking
target_link_libraries(${PROJECT_NAME} PRIVATE
    stb_image
    glad
)

add_dependencies(${PROJECT_NAME} 
    stb_image
    glad
)
