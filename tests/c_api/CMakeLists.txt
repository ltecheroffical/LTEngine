# CMocka
add_subdirectory(thirdparty/cmocka)

# Building tests
add_executable(math_test_vec2 math_test_vec2.c)
add_executable(math_test_rect math_test_rect.c)

target_link_libraries(math_test_vec2 PRIVATE LTEngine cmocka)
target_link_libraries(math_test_rect PRIVATE LTEngine cmocka)


# Math tests
add_test(c_vec2_test math_test_vec2)
add_test(c_rect_test math_test_rect)
