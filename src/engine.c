#include <stdlib.h>

#include <LTEngine/engine.h>


ltengine_t ltengine_new() {
    ltengine_t engine;

    engine.structure = NULL;

    engine.scenes.count = 0;
    engine.scenes.capacity = 4;
    engine.scenes.data = (struct ltengine_scene_t *)calloc(engine.scenes.capacity, sizeof(struct ltengine_scene_t));

    engine.display_initilized = false;
    return engine;
}

void ltengine_free(ltengine_t *engine) {
    for (u32 i = 0; i < engine->scenes.count; i++) {
        if (engine->scenes.data[i].allocated) {
            free(engine->scenes.data[i].data);
        }
    }

    if (engine->display_initilized) {
        ltrenderer_free(&engine->renderer);
    }

    if (engine->structure != NULL) {
        engine->structure->deinit(engine->structure);
    }

    free(engine->scenes.data);
}


void ltengine_init_display(ltengine_t *engine, u32 width, u32 height) {
    if (engine->display_initilized) {
        return;
    }
    
    engine->display_initilized = true;
    engine->renderer = ltrenderer_new(width, height);
}

void ltengine_resize_display(ltengine_t *engine, u32 width, u32 height) {
    ltrenderer_resize(&engine->renderer, width, height);
}

u32 ltengine_get_pixels(ltengine_t *engine, u8 *pixels) {
    if (pixels != NULL) {
        ltrenderer_get_screen_data(&engine->renderer, pixels);
    }

    return ltrenderer_get_buffer_size(&engine->renderer);
}


void ltengine_set_structure(ltengine_t *engine, ltobject_structure_t *structure) {
    engine->structure = structure;
    engine->structure->init(engine->structure);
}

void ltengine_clear_objects(ltengine_t *engine) {
    engine->structure->clear(engine->structure);
}


u32 ltengine_capture_scene(ltengine_t *engine) {
    if (engine->scenes.count >= engine->scenes.capacity) {
        engine->scenes.capacity *= 2;
        engine->scenes.data = (struct ltengine_scene_t *)realloc(engine->scenes.data, engine->scenes.capacity * sizeof(struct ltengine_scene_t));
    }

    u32 state_size = engine->structure->save_state(engine->structure, NULL);
    u8 *state = (u8 *)malloc(state_size);
    engine->structure->save_state(engine->structure, state);

    u32 index = engine->scenes.count++;
    engine->scenes.data[index].allocated = true;
    engine->scenes.data[index].data = state;
    engine->scenes.data[index].size = state_size;
    return index;
}

void ltengine_load_scene(ltengine_t *engine, u32 index) {
    if (index >= engine->scenes.count) {
        return;
    }

    engine->structure->load_state(engine->structure, 
                                  engine->scenes.data[index].data,
                                  engine->scenes.data[index].size);
}

void ltengine_free_scene(ltengine_t *engine, u32 scene) {
    if (scene >= engine->scenes.count) {
        return;
    }

    if (!engine->scenes.data[scene].allocated) {
        return;
    }

    free(engine->scenes.data[scene].data);
    engine->scenes.data[scene].allocated = false;
}


void ltengine_update(ltengine_t *engine, f32 delta) {
    if (engine->structure == NULL) {
        return;
    }
    engine->structure->update(engine->structure, delta);
}

void ltengine_render(ltengine_t *engine) {
    if (!engine->display_initilized) {
        return;
    }
    
    if (engine->structure == NULL) {
        return;
    }
    
    ltrenderer_clear(&engine->renderer, ltcolora_from(engine->structure->clear_color));

    engine->structure->render(engine->structure, &engine->renderer);
}
