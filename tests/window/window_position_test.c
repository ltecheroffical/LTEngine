#include <stdio.h>

#include <LTEngine/window.h>
#include <LTEngine/random.h>


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

    ltresult_ltwindow_t window_result = ltwindow_new(backend, NULL, "SDL Test", SCREEN_WIDTH, SCREEN_HEIGHT);
    
    if (ltresult_ltwindow_get_result(window_result) != LTRESULT_SUCCESS) {
        printf("Test: Could not create window\n");
        return 1;
    }

    ltwindow_t window = ltresult_ltwindow_get_value(window_result);


    u32 mode_w = 0;
    u32 mode_h = 0;

    if (backend == LTWINDOW_BACKEND_GLFW) {
        const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        mode_w = mode->width;
        mode_h = mode->height;
#ifdef LTENGINE_SDL_ENABLE
    } else if (backend == LTWINDOW_BACKEND_SDL) {
        SDL_DisplayMode mode;

        SDL_GetDesktopDisplayMode(0, &mode);

        mode_w = mode.w;
        mode_h = mode.h;
#endif
    }
    

    ltwindow_poll_events(&window);
    

    ltrandom_t random = ltrandom_new_c_random();

    ltrandom_seed(&random, time(NULL));

    u32 rnd_x = ltrandom_get_u32(&random) % (mode_w - 10);
    u32 rnd_y = ltrandom_get_u32(&random) % (mode_h - 10);

    ltwindow_set_position(&window, rnd_x, rnd_y);

    ltwindow_poll_events(&window);

    ltvec2i_t position = ltwindow_get_position(&window);
    
    if (position.x != rnd_x) {
        printf("Test: Failed position comparsion (X)\n");
        ltwindow_destroy(&window);
        return 1;
    }
    if (position.y != rnd_y) {
        printf("Test: Failed position comparsion (Y)\n");
        ltwindow_destroy(&window);
        return 1;
    }

    ltwindow_destroy(&window);
    printf("Test: Test passed!\n");
    return 0;
}
