function(add_sdl_tests)
    add_executable(window_sdl_resize_test window_sdl_resize_test.c)

    target_link_libraries(window_sdl_resize_test PRIVATE LTEngine)

    add_test(NAME window_sdl_resize_test COMMAND window_sdl_resize_test)
endfunction()


if (LTENGINE_BUILD_WITH_SDL)
    add_sdl_tests()
endif()
