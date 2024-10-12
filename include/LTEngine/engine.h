#pragma once

#include <LTEngine/rendering/rendering.h>


typedef struct ltobject_structure_t {
    ltcolor_t clear_color;

    void (*init)(struct ltobject_structure_t*);
    void (*deinit)(struct ltobject_structure_t*);

    void (*update)(struct ltobject_structure_t*, f32);
    void (*render)(struct ltobject_structure_t*, ltrenderer_t*);

    void (*clear)(struct ltobject_structure_t*);

    u32  (*save_state)(const struct ltobject_structure_t*, u8 *data);
    void (*load_state)(struct ltobject_structure_t*, const u8 *data, u32 size);
} ltobject_structure_t;


typedef struct {
    bool display_initilized;
    ltrenderer_t renderer;

    struct {
        struct ltengine_scene_t {
            u8 *data;
            u32 size;
            bool allocated:1;
        } *data;
        u32 count;
        u32 capacity;
    } scenes;

    ltobject_structure_t *structure;
} ltengine_t;


ltengine_t ltengine_new();
void ltengine_free(ltengine_t *engine);

void ltengine_init_display(ltengine_t *engine, u32 width, u32 height);
void ltengine_resize_display(ltengine_t *engine, u32 width, u32 height);
u32 ltengine_get_pixels(ltengine_t *engine, u8 *data);

void ltengine_set_structure(ltengine_t *engine, ltobject_structure_t *structure);
void ltengine_clear_objects(ltengine_t *engine);

u32 ltengine_capture_scene(ltengine_t *engine);
void ltengine_load_scene(ltengine_t *engine, u32 scene);
void ltengine_free_scene(ltengine_t *engine, u32 scene);

void ltengine_update(ltengine_t *engine, f32 delta);
void ltengine_render(ltengine_t *engine);
