#pragma once

#include <LTEngine/common/types/inttypes.h>
#include <LTEngine/common/types/booltypes.h>
#include <LTEngine/common/result.h>

#include <LTEngine/math/vec2.h>
#include <LTEngine/math/rect.h>

#include "colors.h"
#include "camera.h"
#include "cpu_texture.h"


typedef struct {
    u32 _width, _height;
    ltvec2_t _scale;

    union {
        struct {
            struct {
                bool unsafe:1;

                bool screen_only:1;

                bool flip_h:1;
                bool flip_v:1;
            } renderer;
        };
        u8 raw;
    } _flags;

    struct { 
        ltrenderer_camera_t *cams; 
        u32 size;
    } _cams; 

    union {
        struct {
            ltcolor_t *pixels;

            struct {
                u32 width, height;
                u32 size;
                ltcolora_t *data;
            } buffer;
        } _software;
    };

    struct {
        struct ltrenderer_op_t {
            enum {
                LTRENDERER_OP_SET_PARAM = 0,
                LTRENDERER_OP_UPDATE_CAM,

                LTRENDERER_OP_RENDER_CLEAR,

                LTRENDERER_OP_SET_PIXEL,

                LTRENDERER_OP_RENDER_CAM,

                LTRENDERER_OP_RENDER_SQUARE,
                LTRENDERER_OP_RENDER_SPRITE
            } op;

            union {
                struct {
                    enum {
                        LTRENDERER_OP_PARAM_SCREEN_ONLY = 0,

                        LTRENDERER_OP_PARAM_POS_OFFSET,
                    } param;
                    union {
                        bool screen_only:1;
                        ltvec2_t pos_offset;
                    };
                } op_set_param;
                struct {
                    enum {
                        LTRENDERER_OP_CAM_PARAM_POSITION = 0,
                        LTRENDERER_OP_CAM_PARAM_ZOOM,
                        LTRENDERER_OP_CAM_PARAM_EXCLUSION,
                    } param;
                    u32 id;
                    union {
                        ltvec2_t position;
                        ltvec2_t zoom;
                        bool exculde;
                    };
                } op_update_cam;

                struct {
                    ltcolora_t clear_color;
                } op_clear;
                
                struct {
                    ltvec2i_t pos;
                    ltcolora_t color;
                } op_set_pixel;

                struct {
                    u32 id;
                    ltvec2_t position;
                    ltvec2u_t size;
                } op_render_camera;

                struct {
                    ltrecti_t rect;
                    ltcolora_t color;
                } op_render_square;
                struct {
                    ltvec2i_t pos;
                    ltrecti_t region;
                    const lttexture_cpu_t *texture;
                    ltvec2_t scale;
                    ltcolora_t color;
                } op_render_sprite;
            };

            u32 order;

            struct {
                bool active:1;
                bool locked:1;
            } flags;
        } *operations;
        u32 capicity;
        u32 op_count;
        u32 current;

        u32 current_order;
        u32 next_order;
    } _op_queue;

    ltvec2_t _pos_offset;

    u64 _creation_time;
} ltrenderer_t;


ltrenderer_t ltrenderer_new(u32 width, u32 height);
void ltrenderer_free(ltrenderer_t *renderer);

// Processes an operation off a queue
bool ltrenderer_process(ltrenderer_t *renderer);

// Disables some checks and allows some operations allowing UB to happen
void ltrenderer_set_unsafe(ltrenderer_t *renderer);
// Enables all checks
void ltrenderer_clear_unsafe(ltrenderer_t *renderer);

// Makes the renderer render only to the screen
void ltrenderer_set_screen_only(ltrenderer_t *renderer);
// Makes the renderer render to the cameras
void ltrenderer_clear_screen_only(ltrenderer_t *renderer);

// Creates a camera and returns an id
u32 ltrenderer_create_camera(ltrenderer_t *renderer, ltvec2_t position, ltvec2_t zoom);
// Destroys a camera with the given id
void ltrenderer_destroy_camera(ltrenderer_t *renderer, u32 id);
// Sets the position of the camera
void ltrenderer_set_camera_position(ltrenderer_t *renderer, u32 id, ltvec2_t position);
// Sets the zoom of the camera
void ltrenderer_set_camera_zoom(ltrenderer_t *renderer, u32 id, ltvec2_t zoom);
// Excludes a camera from getting renderered to
void ltrenderer_exclude_camera(ltrenderer_t *renderer, u32 id);
// Gets the current camera position
ltvec2i_t ltrenderer_get_camera_position(const ltrenderer_t *renderer, u32 id);
// Gets the current camera zoom
ltvec2_t ltrenderer_get_camera_zoom(const ltrenderer_t *renderer, u32 id);
// Includes a camera
void ltrenderer_include_camera(ltrenderer_t *renderer, u32 id);
// Includes all cameras
void ltrenderer_include_cameras(ltrenderer_t *renderer);

// Resizes the renderer
ltresult_t ltrenderer_resize(ltrenderer_t *renderer, u32 width, u32 height);

// Clears the renderer with the color
void ltrenderer_clear(ltrenderer_t *renderer, ltcolora_t color);

// Draws a pixel
void ltrenderer_set_pixela(ltrenderer_t *renderer, ltvec2i_t position, ltcolora_t color);
// Gets a pixel
ltcolor_t ltrenderer_get_pixel(const ltrenderer_t *renderer, ltvec2i_t position);


// Gets the buffer size of the screen
u32 ltrenderer_get_buffer_size(const ltrenderer_t *renderer);

// Gets the screen size in pixels
ltvec2u_t ltrenderer_get_screen_size(const ltrenderer_t *renderer);
// Gets the screen data
void ltrenderer_get_screen_data(const ltrenderer_t *renderer, u8 *pixels);

void ltrenderer_set_position_offset(ltrenderer_t *renderer, ltvec2_t offset);

void ltrenderer_draw_rect(ltrenderer_t *renderer, ltrect_t rect, ltcolora_t color);
void ltrenderer_draw_line(ltrenderer_t *renderer, ltvec2_t a, ltvec2_t b, u16 thickness, ltcolora_t color);

void ltrenderer_draw_camera(ltrenderer_t *renderer, u32 id, ltvec2_t position, ltvec2u_t size);

void ltrenderer_draw_cpu_texture(ltrenderer_t *renderer, const lttexture_cpu_t *texture, ltvec2_t position, ltcolora_t color);
void ltrenderer_draw_cpu_texture_region(ltrenderer_t *renderer, const lttexture_cpu_t *texture, ltvec2_t position, ltrecti_t region, ltcolora_t color);
