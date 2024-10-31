#include <stdlib.h>

#include <LTEngine/engine.h>


ltengine_t ltengine_new() {
    ltengine_t engine;

    engine._structure = NULL;

    engine._flags.enable_multithreading = false;

    engine._scenes.count = 0;
    engine._scenes.capacity = 4;
    engine._scenes.data = (struct ltengine_scene_t *)calloc(engine._scenes.capacity, sizeof(struct ltengine_scene_t));

    engine._display_initilized = false;
    return engine;
}

void ltengine_free(ltengine_t *engine) {
    for (u32 i = 0; i < engine->_scenes.count; i++) {
        if (engine->_scenes.data[i].allocated) {
            engine->_structure->deinit(engine->_structure);
        }
    }

    if (engine->_display_initilized) {
        ltrenderer_free(engine->_renderer);
    }

    if (engine->_structure != NULL) {
        engine->_structure->deinit(engine->_structure);
    }

    free(engine->_scenes.data);
}


void ltengine_init_display(ltengine_t *engine, ltrenderer_t *renderer) {
    if (engine->_display_initilized) {
        return;
    }
    
    engine->_display_initilized = true;
    engine->_renderer = renderer;
}


void ltengine_set_structure(ltengine_t *engine, ltcustom_structure_t *structure) {
    engine->_structure = structure;
    engine->_structure->init(engine->_structure);
}

void ltengine_clear_objects(ltengine_t *engine) {
    engine->_structure->clear(engine->_structure);
}


void ltengine_use_multithreading(ltengine_t *engine) {
    engine->_flags.enable_multithreading = true;
}

void ltengine_process_frame(ltengine_t *engine) {
    if (!engine->_display_initilized) {
        return;
    }
}


u32 ltengine_capture_scene(ltengine_t *engine) {
    if (engine->_scenes.count >= engine->_scenes.capacity) {
        engine->_scenes.capacity *= 2;
        engine->_scenes.data = (struct ltengine_scene_t *)realloc(engine->_scenes.data, engine->_scenes.capacity * sizeof(struct ltengine_scene_t));
    }


    u32 index = engine->_scenes.count++;

    engine->_scenes.data[index].structure = engine->_structure->clone(engine->_structure);
    engine->_scenes.data[index].allocated = true;

    return index;
}

void ltengine_load_scene(ltengine_t *engine, u32 index) {
    if (index >= engine->_scenes.count) {
        return;
    }

    if (!engine->_scenes.data[index].allocated) {
        return;
    }


    if (engine->_structure != NULL) {
        engine->_structure->deinit(engine->_structure);
    }

    engine->_structure = engine->_scenes.data[index].structure->clone(engine->_scenes.data[index].structure);
}

void ltengine_free_scene(ltengine_t *engine, u32 scene) {
    if (scene >= engine->_scenes.count) {
        return;
    }

    if (!engine->_scenes.data[scene].allocated) {
        return;
    }

    engine->_scenes.data[scene].structure->deinit(engine->_scenes.data[scene].structure);
    engine->_scenes.data[scene].allocated = false;
}


void ltengine_update(ltengine_t *engine, f32 delta) {
    if (engine->_structure == NULL) {
        return;
    }
    engine->_structure->update(engine->_structure, delta);
}

void ltengine_render(ltengine_t *engine) {
    if (!engine->_display_initilized) {
        return;
    }
    
    if (engine->_structure == NULL) {
        return;
    }
   
    ltrenderer_clear(engine->_renderer, ltcolora_from(engine->_structure->clear_color));

    engine->_structure->render(engine->_structure, engine->_renderer);
}
