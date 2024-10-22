#include <LTEngine/engine.h>
#include <LTEngine/window.h>


#define SCREEN_WIDTH  ((u32)500)
#define SCREEN_HEIGHT ((u32)400)



int main(int argc, char **argv) {
    ltengine_t engine = ltengine_new();
    ltresult_ltwindow_t window_res = ltwindow_new(LTWINDOW_BACKEND_GLFW, &engine, "Pong", SCREEN_WIDTH, SCREEN_HEIGHT);
    
    if (ltresult_ltwindow_get_result(window_res) != LTRESULT_SUCCESS) {
        ltengine_free(&engine);
        return 1;
    }
    
    ltwindow_t window = ltresult_ltwindow_get_value(window_res);

    ltwindow_set_resizable(&window, false);
    ltwindow_set_fullscreen(&window, true);

    u32 frames = 0;

    
    while (ltwindow_is_open(&window)) {
        ltwindow_poll_events(&window);
        ltwindow_set_fullscreen(&window, !ltwindow_is_fullscreen(&window));
    }

    ltwindow_destroy(&window);
    ltengine_free(&engine);
}
