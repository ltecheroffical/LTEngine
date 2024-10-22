project(Pong VERSION 1.0.0 LANGUAGES C)


file(GLOB_RECURSE C_SOURCE_FILES CONFIGURE_DEPENDS 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)


if (NOT TARGET ${PROJECT_NAME})
    add_executable(${PROJECT_NAME} ${C_SOURCE_FILES})

    target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src)
endif()

target_link_libraries(${PROJECT_NAME}
    PRIVATE LTEngine)
