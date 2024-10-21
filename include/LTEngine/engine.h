#pragma once

#include <LTEngine/rendering/rendering.h>


struct ltengine_t;

typedef struct ltcustom_structure_t {
    struct ltengine_t *engine;
    ltcolor_t clear_color;

    void (*init)(struct ltcustom_structure_t*);
    void (*deinit)(struct ltcustom_structure_t*);

    void (*update)(struct ltcustom_structure_t*, f32);
    void (*render)(struct ltcustom_structure_t*, ltrenderer_t*);

    void (*clear)(struct ltcustom_structure_t*);

    struct ltcustom_structure_t *(*clone)(const struct ltcustom_structure_t*);
} ltcustom_structure_t;


typedef struct ltengine_t {
    bool _display_initilized;
    ltrenderer_t _renderer;

    struct {
        bool enable_multithreading:1;
    } _flags;

    struct {
        struct ltengine_scene_t {
            ltcustom_structure_t *structure;
            bool allocated:1;
        } *data;
        u32 count;
        u32 capacity;
    } _scenes;

    ltcustom_structure_t *_structure;
} ltengine_t;


ltengine_t ltengine_new();
void ltengine_free(ltengine_t *engine);

void ltengine_init_display(ltengine_t *engine, u32 width, u32 height);
void ltengine_resize_display(ltengine_t *engine, u32 width, u32 height);
u32 ltengine_get_pixels(ltengine_t *engine, u8 *data);

void ltengine_set_structure(ltengine_t *engine, ltcustom_structure_t *structure);
void ltengine_clear_objects(ltengine_t *engine);

void ltengine_use_multithreading(ltengine_t *engine);
void ltengine_process_frame(ltengine_t *engine);

u32 ltengine_capture_scene(ltengine_t *engine);
void ltengine_load_scene(ltengine_t *engine, u32 scene);
void ltengine_free_scene(ltengine_t *engine, u32 scene);

void ltengine_update(ltengine_t *engine, f32 delta);
void ltengine_render(ltengine_t *engine);
