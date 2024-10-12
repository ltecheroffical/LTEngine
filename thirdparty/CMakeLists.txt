add_subdirectory(stb_image)


target_link_libraries(${PROJECT_NAME} PRIVATE
    stb_image
)

add_dependencies(${PROJECT_NAME} 
    stb_image
)
