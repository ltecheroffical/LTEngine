#include <stdio.h>
#include <assert.h>

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

    ltresult_ltwindow_t window_result = ltwindow_new(backend, NULL, backend == LTWINDOW_BACKEND_SDL ? "SDL Test" : "GLFW Test", MAX_WIDTH, MAX_HEIGHT);

    assert(ltresult_ltwindow_get_result(window_result) == LTRESULT_SUCCESS);

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

    assert(size.x == rnd_width);
    assert(size.y == rnd_height);

    ltwindow_destroy(&window);
    printf("Test: Test passed!\n");
    return 0;    
}
