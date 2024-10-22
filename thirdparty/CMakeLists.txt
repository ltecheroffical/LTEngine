# Rendering
add_subdirectory(stb_image)

# Windowing
if (LTENGINE_BUILD_WITH_SDL)
    add_subdirectory(SDL)
endif()

add_subdirectory(glfw)

target_link_libraries(${PROJECT_NAME} PUBLIC
    glfw
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
)

add_dependencies(${PROJECT_NAME} 
    stb_image
)
