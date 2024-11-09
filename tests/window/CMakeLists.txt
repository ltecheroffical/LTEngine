add_executable(glfw_window_test glfw_window_test.cpp)

target_link_libraries(glfw_window_test PRIVATE LTEngine)

add_dependencies(glfw_window_test 
    LTEngine)


add_test(NAME window_glfw_resize_test COMMAND glfw_window_test test_window_resize)
add_test(NAME window_glfw_position_test COMMAND glfw_window_test test_window_position)
add_test(NAME window_glfw_title_test COMMAND glfw_window_test test_window_title)
add_test(NAME window_glfw_minimize_test COMMAND glfw_window_test test_window_minimize)


if (LTENGINE_BUILD_WITH_SDL)
    add_executable(sdl_window_test sdl_window_test.cpp)

    target_link_libraries(sdl_window_test PRIVATE LTEngine)

    add_dependencies(sdl_window_test
        LTEngine)


    add_test(NAME window_sdl_resize_test COMMAND sdl_window_test test_window_resize)
    add_test(NAME window_sdl_position_test COMMAND sdl_window_test test_window_position)
    add_test(NAME window_sdl_title_test COMMAND sdl_window_test test_window_title)
    add_test(NAME window_sdl_minimize_test COMMAND sdl_window_test test_window_minimize)
endif()
