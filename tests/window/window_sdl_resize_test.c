#include <stdio.h>

#include <LTEngine/window.h>
#include <LTEngine/random.h>
#include <time.h>


i32 main(i32 argc, char *argv[]) {
    ltresult_ltwindow_t window_result = ltwindow_new(LTWINDOW_BACKEND_SDL, NULL, "SDL Test", 640, 480);

    if (ltresult_ltwindow_get_result(window_result) != LTRESULT_SUCCESS) {
        printf("Test: Could not create window\n");
    }

    ltwindow_t window = ltresult_ltwindow_get_value(window_result);


    ltrandom_t random = ltrandom_new_c_random();

    // Get random size
    ltrandom_seed(&random, time(NULL));
    u32 rnd_width = ltrandom_get_u32(&random) % 640;
    u32 rnd_height = ltrandom_get_u32(&random) % 480;

    ltwindow_poll_events(&window);

    ltwindow_set_size(&window, rnd_width, rnd_height);

    ltwindow_poll_events(&window);

    ltvec2i_t size = ltwindow_get_size(&window);

    if (size.x != rnd_width) {
        printf("Test: Failed size comparsion (Width)\n");
        ltwindow_destroy(&window);
        return 1;
    }
    if (size.y != rnd_height) {
        printf("Test: Failed size comparsion (Height)\n");
        ltwindow_destroy(&window);
        return 1;
    }

    ltwindow_destroy(&window);
    printf("Test: Test passed!\n");
    return 0;    
}
