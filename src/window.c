#include <GLFW/glfw3.h>
#ifdef LTENGINE_SDL_ENABLE
#include <SDL2/SDL.h>
#endif


#include <LTEngine/window.h>


ltresult_ltwindow_t ltwindow_new(enum ltwindow_backend_t backend, const ltengine_t *engine, const char *title, u32 width, u32 height) {
    ltwindow_t window;

    window._backend = backend;
    window._engine = engine;

    switch (backend) {
        case LTWINDOW_BACKEND_GLFW:
            glfwInit();

            GLFWwindow *glfw_window = glfwCreateWindow(width, height, title, NULL, NULL);

            if (glfw_window == NULL) {
                return ltresult_ltwindow_new(LTRESULT_FATAL_ERROR, window);
            }

            window._glfw.width = 0;
            window._glfw.height = 0;

            window._glfw.window = glfw_window;
            break;

#ifdef LTENGINE_SDL_ENABLE
        case LTWINDOW_BACKEND_SDL: {
            SDL_Window *sdl_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

            if (sdl_window == NULL) {
                return ltresult_ltwindow_new(LTRESULT_FATAL_ERROR, window);
            }

            window._sdl.is_open = true;
            window._sdl.window = sdl_window;
            break;
        }
#endif
            
        default:
            return ltresult_ltwindow_new(LTRESULT_ERR_NOT_IMPLEMENTED, window);
            break;
    }

    return ltresult_ltwindow_new(LTRESULT_SUCCESS, window);
}

void ltwindow_destroy(ltwindow_t *window) {
    switch (window->_backend) {
        case LTWINDOW_BACKEND_GLFW:
            glfwDestroyWindow(window->_glfw.window);
            break;

#ifdef LTENGINE_SDL_ENABLE
        case LTWINDOW_BACKEND_SDL:
            SDL_DestroyWindow(window->_sdl.window);
            break;
#endif
            
        default:
            break;
    }
}


void ltwindow_poll_events(ltwindow_t *window) {
    switch (window->_backend) {
        case LTWINDOW_BACKEND_GLFW:
            glfwPollEvents();
            break;

#ifdef LTENGINE_SDL_ENABLE
        case LTWINDOW_BACKEND_SDL: {
            SDL_Event event;

            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    window->_sdl.is_open = false;
                    break;
                }
            }
            break;
        }
#endif
            
        default:
            break;
    }
}

bool ltwindow_is_open(ltwindow_t *window) {
    switch (window->_backend) {
        case LTWINDOW_BACKEND_GLFW:
            return !glfwWindowShouldClose(window->_glfw.window);

#ifdef LTENGINE_SDL_ENABLE
        case LTWINDOW_BACKEND_SDL:
            return window->_sdl.is_open;
#endif
            
        default:
            return false;
    }
}


void ltwindow_set_title(ltwindow_t *window, const char *title) {
    switch (window->_backend) {
        case LTWINDOW_BACKEND_GLFW:
            glfwSetWindowTitle(window->_glfw.window, title);
            break;

#ifdef LTENGINE_SDL_ENABLE
        case LTWINDOW_BACKEND_SDL:
            SDL_SetWindowTitle(window->_sdl.window, title);
            break;
#endif
            
        default:
            break;
    }
}

const char *ltwindow_get_title(ltwindow_t *window) {
    switch (window->_backend) {
        case LTWINDOW_BACKEND_GLFW:
            return glfwGetWindowTitle(window->_glfw.window);

#ifdef LTENGINE_SDL_ENABLE
        case LTWINDOW_BACKEND_SDL:
            return SDL_GetWindowTitle(window->_sdl.window);
#endif
            
        default:
            return NULL;
    }
}


void ltwindow_set_size(ltwindow_t *window, u32 width, u32 height) {
    switch (window->_backend) {
        case LTWINDOW_BACKEND_GLFW:
            glfwSetWindowSize(window->_glfw.window, width, height);
            break;
        
#ifdef LTENGINE_SDL_ENABLE
        case LTWINDOW_BACKEND_SDL:
            SDL_SetWindowSize(window->_sdl.window, width, height);
            break;
#endif
            
        default:
            break;
    }
}

void ltwindow_set_position(ltwindow_t *window, u32 x, u32 y) {
    switch (window->_backend) {
        case LTWINDOW_BACKEND_GLFW:
            glfwSetWindowPos(window->_glfw.window, x, y);
            break;
        
#ifdef LTENGINE_SDL_ENABLE
        case LTWINDOW_BACKEND_SDL:
            SDL_SetWindowPosition(window->_sdl.window, x, y);
            break;
#endif
            
        default:
            break;
    }
}

void ltwindow_set_resizable(ltwindow_t *window, bool resizable) {
    switch (window->_backend) {
        case LTWINDOW_BACKEND_GLFW:
            glfwSetWindowAttrib(window->_glfw.window, GLFW_RESIZABLE, resizable);
            break;
        
#ifdef LTENGINE_SDL_ENABLE
        case LTWINDOW_BACKEND_SDL:
            SDL_SetWindowResizable(window->_sdl.window, (SDL_bool)resizable);
            break;
#endif
            
        default:
            break;
    }
}

void ltwindow_set_fullscreen(ltwindow_t *window, bool fullscreen) {
    switch (window->_backend) {
        case LTWINDOW_BACKEND_GLFW:
            if (fullscreen) {
                int width, height;
                int x, y;
                glfwGetWindowSize(window->_glfw.window, &width, &height);
                glfwGetWindowPos(window->_glfw.window, &x, &y);
                
                window->_glfw.width = width;
                window->_glfw.height = height;
                window->_glfw.position.x = x;
                window->_glfw.position.y = y;


                const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

                glfwSetWindowMonitor(window->_glfw.window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
            } else {
                if (!ltwindow_is_fullscreen(window)) {
                    break;
                }
                glfwSetWindowMonitor(window->_glfw.window, NULL, 
                                     window->_glfw.position.x, window->_glfw.position.y,
                                     window->_glfw.width, window->_glfw.height, GLFW_DONT_CARE);
            }
            break;

#ifdef LTENGINE_SDL_ENABLE
        case LTWINDOW_BACKEND_SDL:
            if (fullscreen) {
                SDL_SetWindowFullscreen(window->_sdl.window, SDL_WINDOW_FULLSCREEN_DESKTOP);
            } else {
                SDL_SetWindowFullscreen(window->_sdl.window, 0);
            }
            break;
#endif
            
        default:
            break;
    }
}


ltvec2i_t ltwindow_get_size(ltwindow_t *window) {
    switch (window->_backend) {
        case LTWINDOW_BACKEND_GLFW: {
            int width, height;
            glfwGetWindowSize(window->_glfw.window, &width, &height);
            return ltvec2i_new(width, height);
        }
        
#ifdef LTENGINE_SDL_ENABLE
        case LTWINDOW_BACKEND_SDL: {
            int width, height;
            SDL_GetWindowSize(window->_sdl.window, &width, &height);
            return ltvec2i_new(width, height);
        }
#endif
            
        default:
            return LTVEC2I_ZERO;
    }
}

ltvec2i_t ltwindow_get_position(ltwindow_t *window) {
    switch (window->_backend) {
        case LTWINDOW_BACKEND_GLFW: {
            int x, y;
            glfwGetWindowPos(window->_glfw.window, &x, &y);
            return ltvec2i_new(x, y);
        }
        
#ifdef LTENGINE_SDL_ENABLE
        case LTWINDOW_BACKEND_SDL: {
            int x, y;
            SDL_GetWindowPosition(window->_sdl.window, &x, &y);
            return ltvec2i_new(x, y);
        }
#endif
            
        default:
            return LTVEC2I_ZERO;
    }
}

bool ltwindow_is_resizable(ltwindow_t *window) {
    switch (window->_backend) {
        case LTWINDOW_BACKEND_GLFW:
            return glfwGetWindowAttrib(window->_glfw.window, GLFW_RESIZABLE);

#ifdef LTENGINE_SDL_ENABLE
        case LTWINDOW_BACKEND_SDL:
            return SDL_GetWindowFlags(window->_sdl.window) & SDL_WINDOW_RESIZABLE;
#endif
            
        default:
            return false;
    }
}

bool ltwindow_is_fullscreen(ltwindow_t *window) {
    switch (window->_backend) {
        case LTWINDOW_BACKEND_GLFW:
            return glfwGetWindowMonitor(window->_glfw.window) != NULL;

#ifdef LTENGINE_SDL_ENABLE
        case LTWINDOW_BACKEND_SDL:
            return SDL_GetWindowFlags(window->_sdl.window) & SDL_WINDOW_FULLSCREEN;
#endif
            
        default:
            return false;
    }
}


void ltwindow_hide(ltwindow_t *window) {
    switch (window->_backend) {
        case LTWINDOW_BACKEND_GLFW:
            glfwHideWindow(window->_glfw.window);
            break;
        
#ifdef LTENGINE_SDL_ENABLE
        case LTWINDOW_BACKEND_SDL:
            SDL_HideWindow(window->_sdl.window);
            break;
#endif
            
        default:
            break;
    }
}

void ltwindow_show(ltwindow_t *window) {
    switch (window->_backend) {
        case LTWINDOW_BACKEND_GLFW:
            glfwShowWindow(window->_glfw.window);
            break;
        
#ifdef LTENGINE_SDL_ENABLE
        case LTWINDOW_BACKEND_SDL:
            SDL_ShowWindow(window->_sdl.window);
            break;
#endif
            
        default:
            break;
    }
}

void ltwindow_set_minimized(ltwindow_t *window, bool minimized) {
    switch (window->_backend) {
        case LTWINDOW_BACKEND_GLFW:
            if (minimized) {
                glfwIconifyWindow(window->_glfw.window);
            } else {
                glfwRestoreWindow(window->_glfw.window);
            }
            break;

#ifdef LTENGINE_SDL_ENABLE
        case LTWINDOW_BACKEND_SDL:
            if (minimized) {
                SDL_MinimizeWindow(window->_sdl.window);
            } else {
                SDL_RestoreWindow(window->_sdl.window);
            }
            break;
#endif
            
        default:
            break;
    }
}

bool ltwindow_is_minimized(ltwindow_t *window) {
    switch (window->_backend) {
        case LTWINDOW_BACKEND_GLFW:
            return glfwGetWindowAttrib(window->_glfw.window, GLFW_ICONIFIED);

#ifdef LTENGINE_SDL_ENABLE
        case LTWINDOW_BACKEND_SDL:
            return SDL_GetWindowFlags(window->_sdl.window) & SDL_WINDOW_MINIMIZED;
#endif
            
        default:
            return false;
    }
}
