#pragma once

#include <LTEngine/common/types/inttypes.h>
#include <LTEngine/common/types/booltypes.h>
#include <LTEngine/common/result.h>

#include <LTEngine/math/vec2.h>
#include <LTEngine/math/rect.h>

#include <LTEngine/rendering/colors.h>
#include <LTEngine/rendering/camera.h>
#include <LTEngine/rendering/image.h>


#define LTRENDERER_FLAG_FLIP_H ((ltrenderer_flags_t)(1 << 0))
#define LTRENDERER_FLAG_FLIP_V ((ltrenderer_flags_t)(1 << 1))

#define LTRENDERER_FLAG_POINT_FILL ((ltrenderer_flags_t)(1 << 8))

typedef u16 ltrenderer_flags_t;


typedef struct ltrenderer_t {
    struct ltrenderer_module_t {
        void (*free)(struct ltrenderer_module_t *module);

        void (*set_scale)(struct ltrenderer_module_t *module, ltvec2_t scale);
        void (*set_rotation)(struct ltrenderer_module_t *module, f32 rotation);

        void (*set_z)(struct ltrenderer_module_t *module, u16 z);

        void (*set_active_camera)(struct ltrenderer_module_t *module, u32 id);
        void (*clear_active_camera)(struct ltrenderer_module_t *module);

        void (*set_iris_mode)(struct ltrenderer_module_t *module);
        void (*clear_iris_mode)(struct ltrenderer_module_t *module, ltcolora_t color);

        void (*set_pixela)(struct ltrenderer_module_t *module, ltvec2i_t position, ltcolora_t color);
        ltcolor_t (*get_pixel)(const struct ltrenderer_module_t *module, ltvec2i_t position);

        void (*clear)(struct ltrenderer_module_t *module, ltcolora_t color);

        void (*draw_rect)(struct ltrenderer_module_t *module, ltrect_t rect, ltrenderer_flags_t flags, ltcolora_t color);
        void (*draw_circle)(struct ltrenderer_module_t *module, ltvec2_t center, f32 radius, ltrenderer_flags_t flags, ltcolora_t color);

        void (*draw_line)(struct ltrenderer_module_t *module, ltvec2_t a, ltvec2_t b, u16 thickness, ltrenderer_flags_t flags, ltcolora_t color);
        void (*fill_points)(struct ltrenderer_module_t *module, ltvec2_t *points, u32 count, ltrenderer_flags_t flags, ltcolora_t color);

        void (*draw_camera)(struct ltrenderer_module_t *module, u32 id, ltrect_t crop);
    } *_module;

    struct { 
        ltrenderer_camera_t *cams; 
        u32 size;
    } _cams;

    u16 _z_order;

    f32 _rotation;
    ltvec2_t _scale;

    f32 _rotation_offset;
    ltvec2_t _scale_offset;
    ltvec2_t _pos_offset;
} ltrenderer_t;

typedef struct ltrenderer_module_t ltrenderer_module_t;


ltrenderer_t ltrenderer_new(ltrenderer_module_t *module);
void ltrenderer_free(ltrenderer_t *renderer);

// Sets the scale
void ltrenderer_set_scale(ltrenderer_t *renderer, ltvec2_t scale);
// Sets the rotation
void ltrenderer_set_rotation(ltrenderer_t *renderer, f32 rotation);

// Sets the rotation offset
void ltrenderer_set_rotation_offset(ltrenderer_t *renderer, f32 offset);
// Sets the scale offset
void ltrenderer_set_scale_offset(ltrenderer_t *renderer, ltvec2_t offset);
// Sets the position offset
void ltrenderer_set_position_offset(ltrenderer_t *renderer, ltvec2_t offset);

// Sets the Z-Order
void ltrenderer_set_z_order(ltrenderer_t *renderer, u16 z);

// Sets Iris Mode, anything drawn here will be transparent and the rest is filled with color
void ltrenderer_set_iris_mode(ltrenderer_t *renderer);
// Clears the iris mode, the screen will be filled with color except for the iris
void ltrenderer_clear_iris_mode(ltrenderer_t *renderer, ltcolora_t color);

// Creates a camera and returns an id
ltresult_u32_t ltrenderer_create_camera(ltrenderer_t *renderer, ltvec2_t position, ltvec2_t zoom);
// Destroys a camera with the given id
void ltrenderer_destroy_camera(ltrenderer_t *renderer, u32 id);
// Sets the position of the camera
void ltrenderer_set_camera_position(ltrenderer_t *renderer, u32 id, ltvec2_t position);
// Sets the zoom of the camera
void ltrenderer_set_camera_zoom(ltrenderer_t *renderer, u32 id, ltvec2_t zoom);
// Excludes a camera from getting renderered to
void ltrenderer_exclude_camera(ltrenderer_t *renderer, u32 id);
// Includes a camera
void ltrenderer_include_camera(ltrenderer_t *renderer, u32 id);
// Includes all cameras
void ltrenderer_include_cameras(ltrenderer_t *renderer);
// Gets the current camera position
ltvec2i_t ltrenderer_get_camera_position(const ltrenderer_t *renderer, u32 id);
// Gets the current camera zoom
ltvec2_t ltrenderer_get_camera_zoom(const ltrenderer_t *renderer, u32 id);

// Draws a pixel
void ltrenderer_set_pixela(ltrenderer_t *renderer, ltvec2i_t position, ltcolora_t color);
// Gets a pixel
ltcolor_t ltrenderer_get_pixel(const ltrenderer_t *renderer, ltvec2i_t position);

// Clears the renderer with the color
void ltrenderer_clear(ltrenderer_t *renderer, ltcolora_t color);

// Draws a rectangle
void ltrenderer_draw_rect(ltrenderer_t *renderer, ltrect_t rect, ltrenderer_flags_t flags, ltcolora_t color);
// Draws a circle
void ltrenderer_draw_circle(ltrenderer_t *renderer, ltvec2_t center, f32 radius, ltrenderer_flags_t flags, ltcolora_t color);
// Draws a triangle (it really wraps ltrenderer_draw_points)
void ltrenderer_draw_triangle(ltrenderer_t *renderer, ltvec2_t a, ltvec2_t b, ltvec2_t c, ltrenderer_flags_t flags, ltcolora_t color);

// Draws a set of points (really wraps ltrenderer_draw_line)
void ltrenderer_draw_points(ltrenderer_t *renderer, ltvec2_t *points, u32 count, u16 thickness, ltrenderer_flags_t flags, ltcolora_t color);
// Draws a line
void ltrenderer_draw_line(ltrenderer_t *renderer, ltvec2_t a, ltvec2_t b, u16 thickness, ltrenderer_flags_t flags, ltcolora_t color);

// Draws a image
void ltrenderer_draw_image(ltrenderer_t *renderer, ltimage_t *image, ltvec2_t position, ltrenderer_flags_t flags, ltcolora_t color);

// Draws the output of a camera to the screen
void ltrenderer_draw_camera(ltrenderer_t *renderer, u32 id, ltrect_t crop);
