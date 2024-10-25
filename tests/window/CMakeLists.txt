function(add_sdl_tests)
    target_link_libraries(window_resize_test PRIVATE SDL2)
    target_link_libraries(window_position_test PRIVATE SDL2)
    target_link_libraries(window_title_test PRIVATE SDL2)
    target_link_libraries(window_minimize_test PRIVATE SDL2)

    add_test(NAME window_sdl_resize_test COMMAND window_resize_test sdl)
    add_test(NAME window_sdl_position_test COMMAND window_position_test sdl)
    add_test(NAME window_sdl_title_test COMMAND window_title_test sdl)
    add_test(NAME window_sdl_minimize_test COMMAND window_minimize_test sdl)
endfunction()


add_executable(window_resize_test window_resize_test.c)
add_executable(window_position_test window_position_test.c)
add_executable(window_title_test window_title_test.c)
add_executable(window_minimize_test window_minimize_test.c)

target_link_libraries(window_resize_test PRIVATE LTEngine)
target_link_libraries(window_position_test PRIVATE LTEngine)
target_link_libraries(window_title_test PRIVATE LTEngine)
target_link_libraries(window_minimize_test PRIVATE LTEngine)

add_test(NAME window_glfw_resize_test COMMAND window_resize_test glfw)
add_test(NAME window_glfw_position_test COMMAND window_position_test glfw)
add_test(NAME window_glfw_title_test COMMAND window_title_test glfw)
add_test(NAME window_glfw_minimize_test COMMAND window_minimize_test glfw)


if (LTENGINE_BUILD_WITH_SDL)
    add_sdl_tests()
endif()
