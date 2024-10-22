#include <stdio.h>

#include <LTEngine/window.h>
#include <LTEngine/random.h>


#define MAX_WIDTH ((u32)500)
#define MAX_HEIGHT ((u32)400)


i32 main(i32 argc, char *argv[]) {
    if (argc < 2) {
        printf("Test: Missing argument\n");
        return 1;
    }

    enum ltwindow_backend_t backend;

    if (strcmp(argv[1], "glfw") == 0) {
        backend = LTWINDOW_BACKEND_GLFW;
#ifdef LTENGINE_SDL_ENABLE
    } else if (strcmp(argv[1], "sdl") == 0) {
        backend = LTWINDOW_BACKEND_SDL;
#endif
    } else {
        printf("Test: Unknown backend\n");
        return 1;
    }

    ltresult_ltwindow_t window_result = ltwindow_new(backend, NULL, "SDL Test", MAX_WIDTH, MAX_HEIGHT);

    if (ltresult_ltwindow_get_result(window_result) != LTRESULT_SUCCESS) {
        printf("Test: Could not create window\n");
    }

    ltwindow_t window = ltresult_ltwindow_get_value(window_result);


    ltrandom_t random = ltrandom_new_c_random();

    // Get random size
    ltrandom_seed(&random, time(NULL));
    u32 rnd_width = ltrandom_get_u32(&random) % MAX_WIDTH;
    u32 rnd_height = ltrandom_get_u32(&random) % MAX_HEIGHT;

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
