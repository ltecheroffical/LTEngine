#pragma once

#include <GLFW/glfw3.h>
#ifdef LTENGINE_SDL_ENABLE
#include <SDL2/SDL.h>
#endif

#include <LTEngine/common/types/booltypes.h>
#include <LTEngine/common/types/inttypes.h>

#include <LTEngine/common/result.h>

#include <LTEngine/math/vec2.h>

#include <LTEngine/engine.h>


typedef struct {
    enum ltwindow_backend_t : u8 {
        LTWINDOW_BACKEND_GLFW = 0,

#ifdef LTENGINE_SDL_ENABLE
        LTWINDOW_BACKEND_SDL,
#endif
    } _backend;

    union {
        struct {
            GLFWwindow *window;
            u32 width;
            u32 height;
            ltvec2i_t position;
            bool is_minimized:1;
        } _glfw;
        
#ifdef LTENGINE_SDL_ENABLE
        struct {
            SDL_Window *window;
            bool is_open:1;
            bool is_minimized:1;
        } _sdl;
#endif
    };

    const ltengine_t *_engine;
} ltwindow_t;

DEFINE_LTRESULT(ltwindow_t, ltwindow)


ltresult_ltwindow_t ltwindow_new(enum ltwindow_backend_t backend, const ltengine_t *engine, const char *title, u32 width, u32 height);
void ltwindow_destroy(ltwindow_t *window);

void ltwindow_poll_events(ltwindow_t *window);
bool ltwindow_is_open(ltwindow_t *window);

void ltwindow_set_title(ltwindow_t *window, const char *title);
const char *ltwindow_get_title(ltwindow_t *window);

void ltwindow_set_size(ltwindow_t *window, u32 width, u32 height);
void ltwindow_set_position(ltwindow_t *window, u32 x, u32 y);
void ltwindow_set_resizable(ltwindow_t *window, bool resizable);
void ltwindow_set_fullscreen(ltwindow_t *window, bool fullscreen);

ltvec2i_t ltwindow_get_size(ltwindow_t *window);
ltvec2i_t ltwindow_get_position(ltwindow_t *window);
bool ltwindow_is_resizable(ltwindow_t *window);
bool ltwindow_is_fullscreen(ltwindow_t *window);

void ltwindow_hide(ltwindow_t *window);
void ltwindow_show(ltwindow_t *window);
void ltwindow_set_minimized(ltwindow_t *window, bool minimized);
bool ltwindow_is_minimized(ltwindow_t *window);

