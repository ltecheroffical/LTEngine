#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <LTEngine/window.h>
#include <LTEngine/random.h>


#define SCREEN_WIDTH  ((u32)500)
#define SCREEN_HEIGHT ((u32)400)


static char random_characters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()[]{}\\|;:'\",./<>?`~ \t\n";


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


    ltwindow_poll_events(&window);

    
    ltrandom_t random = ltrandom_new_c_random();

    ltrandom_seed(&random, time(NULL));

    u32 rnd_title_length = ltrandom_get_u32(&random) % 64;

    if (rnd_title_length < 5) {
        rnd_title_length = 5;
    }

    char *title = malloc(sizeof(char) * (rnd_title_length + 1));

    if (title == NULL) {
        printf("Test: Failed to allocate title\n");
        ltwindow_destroy(&window);
        return 1;
    }

    printf("Test: Generated Title (If your curious): ");

    for (u32 i = 0; i < rnd_title_length; i++) {
        u8 c = ltrandom_get_u8(&random) % (sizeof(random_characters) - 1);

        title[i] = random_characters[c];
        printf("%c", random_characters[c]);
    }
    
    printf("\n");

    title[rnd_title_length] = '\0';

    ltwindow_set_title(&window, title);

    ltwindow_poll_events(&window);

    
    const char *actual_title = ltwindow_get_title(&window);

    if (strcmp(title, actual_title) != 0) {
        printf("Test: Title comparsion failed\n");
        return 1;
    }

    free(title);
    ltwindow_destroy(&window);
    printf("Test: Test passed!\n");
    return 0;
}
