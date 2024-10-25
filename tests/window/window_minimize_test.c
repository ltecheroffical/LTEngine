#include <assert.h>

#include <LTEngine/window.h>


#define SCREEN_WIDTH  ((u32)500)
#define SCREEN_HEIGHT ((u32)400)


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

    ltresult_ltwindow_t window_result = ltwindow_new(backend, NULL, backend == LTWINDOW_BACKEND_SDL ? "SDL Test" : "GLFW Test", SCREEN_WIDTH, SCREEN_HEIGHT);

    assert(ltresult_ltwindow_get_result(window_result) == LTRESULT_SUCCESS);

    ltwindow_t window = ltresult_ltwindow_get_value(window_result);


    ltwindow_poll_events(&window);

    ltwindow_set_minimized(&window, true);

    ltwindow_poll_events(&window);

    assert(ltwindow_is_minimized(&window) == true);

    ltwindow_set_minimized(&window, false);

    ltwindow_poll_events(&window);

    assert(ltwindow_is_minimized(&window) == false);

    ltwindow_destroy(&window);
    printf("Test: Test passed!\n");
    return 0;
}
