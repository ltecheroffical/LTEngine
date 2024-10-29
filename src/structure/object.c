#include <stdlib.h>
#include <string.h>

#include <LTEngine/structure/object.h>


static void ltobject_structure_init(ltcustom_structure_t *structure);
static void ltobject_structure_deinit(ltcustom_structure_t *structure);
static void ltobject_structure_update(ltcustom_structure_t *structure, f32 delta_time);
static void ltobject_structure_render(ltcustom_structure_t *structure, ltrenderer_t *renderer);
static void ltobject_structure_clear(ltcustom_structure_t *structure);
static ltcustom_structure_t *ltobject_structure_clone(const ltcustom_structure_t *structure);


ltobject_structure_t ltobject_structure_new(ltengine_t *engine) {
    ltobject_structure_t structure;

    structure._structure.engine = engine;
    structure._structure.init = ltobject_structure_init;
    structure._structure.deinit = ltobject_structure_deinit;
    structure._structure.update = ltobject_structure_update;
    structure._structure.render = ltobject_structure_render;
    structure._structure.clear = ltobject_structure_clear;
    structure._structure.clone = ltobject_structure_clone;
 
    return structure;
}


u32 ltobject_structure_add_sub_structure(ltobject_structure_t *structure, ltcustom_structure_t *sub_structure) {
    for (u32 i = 0; i < sizeof(structure->_sub_structures); i++) {
        if (!structure->_sub_structures[i]._flags.in_use) {
            structure->_sub_structures[i]._flags.in_use = true;
            structure->_sub_structures[i].sub_structure = sub_structure;
            return i;
        }
    }
    return UINT32_MAX;
}

void ltobject_structure_remove_sub_structure(ltobject_structure_t *structure, u32 index) {
    structure->_sub_structures[index]._flags.in_use = false;
}

void ltobject_structure_clear_substructure(ltobject_structure_t *structure, u32 index) {
    structure->_sub_structures[index].sub_structure->clear(structure->_sub_structures[index].sub_structure);
}

ltcustom_structure_t *ltobject_structure_get_sub_structure(ltobject_structure_t *structure, u32 index) {
    return structure->_sub_structures[index].sub_structure;
}


void ltobject_structure_set_clear_color(ltobject_structure_t *structure, ltcolor_t color) {
    structure->_structure.clear_color = color;
}


ltobject_t *ltobject_structure_new_object(ltobject_structure_t *structure, void (*init)(ltobject_t *object)) {
    ltobject_t *object = structure->_objects.object_dll;

    while (!object->_flags.free && object->_next != NULL) {
        object = object->_next;
    }

    if (!object->_flags.free) {
        ltobject_t *prev_object = object;

        object = (ltobject_t*)malloc(sizeof(ltobject_t));
        object->_next = NULL;
        object->_prev = prev_object;

        prev_object->_next = object;
    }

    object->_flags.free = false;
    object->_flags.active = true;
    object->_flags.visible = true;

    object->_structure = structure;

    object->position = LTVEC2_ZERO;
    object->scale = LTVEC2_ONE;
    object->rotation = 0.f;

    if (init != NULL) {
        init(object);
    }

    object->_init = init;
    object->deinit = NULL;
    object->render = NULL;
    object->update = NULL;
    object->clone = NULL;

    return object;
}

void ltobject_structure_free_object(ltobject_structure_t *structure, ltobject_t *object) {
    if (object->deinit != NULL) {
        object->deinit(object);
    }

    object->_flags.free = true;
    object->_flags.active = false;
    object->_flags.visible = false;
}




ltobject_t *ltobject_next(ltobject_t *object) {
    return object->_next;
}

ltobject_t *ltobject_prev(ltobject_t *object) {
    return object->_prev;
}


ltobject_structure_t *ltobject_get_structure(ltobject_t *object) {
    return object->_structure;
}


void ltobject_set_active(ltobject_t *object, bool active) {
    object->_flags.active = active;
}

void ltobject_set_visible(ltobject_t *object, bool visible) {
    object->_flags.visible = visible;
}




void ltobject_structure_init(ltcustom_structure_t *structure) {
    ltobject_structure_t *obj_structure = (ltobject_structure_t*)structure;

    for (u32 i = 0; i < MAX_SUB_STRUCTURE_COUNT; i++) {
        obj_structure->_sub_structures[i]._flags.in_use = false;
    }


    obj_structure->_structure.clear_color = LTCOLOR_BLACK;

    obj_structure->_objects.count = 0;
    obj_structure->_objects.object_dll = (ltobject_t*)malloc(sizeof(ltobject_t));
    obj_structure->_objects.object_dll->_next = NULL;
    obj_structure->_objects.object_dll->_prev = NULL;
    obj_structure->_objects.object_dll->_flags.free = true;
    
}

void ltobject_structure_deinit(ltcustom_structure_t *structure) {
    ltobject_structure_t *obj_structure = (ltobject_structure_t*)structure;

    ltobject_t *object = obj_structure->_objects.object_dll;
    while (object != NULL) {
        ltobject_t *next = object->_next;
        ltobject_structure_free_object(obj_structure, object);
        object = next;
    }
}


void ltobject_structure_update(ltcustom_structure_t *structure, f32 delta_time) {
    ltobject_structure_t *obj_structure = (ltobject_structure_t*)structure;

    ltobject_t *object = obj_structure->_objects.object_dll;
    while (object != NULL) {
        if (object->_flags.active && object->update != NULL) {
            object->update(object, delta_time);
        }
        object = object->_next;
    }


    for (u32 i = 0; i < MAX_SUB_STRUCTURE_COUNT; i++) {
        if (obj_structure->_sub_structures[i]._flags.in_use) {
            obj_structure->_sub_structures[i].sub_structure->update(obj_structure->_sub_structures[i].sub_structure, delta_time);
        }
    }
}

void ltobject_structure_render(ltcustom_structure_t *structure, ltrenderer_t *renderer) {
    ltobject_structure_t *obj_structure = (ltobject_structure_t*)structure;

    ltobject_t *object = obj_structure->_objects.object_dll;
    while (object != NULL) {
        if (object->_flags.visible && object->render != NULL) {
            ltrenderer_set_position_offset(renderer, object->position);

            object->render(object, renderer);


            ltrenderer_set_position_offset(renderer, LTVEC2_ZERO);
        }
        object = object->_next;
    }
}


void ltobject_structure_clear(ltcustom_structure_t *structure) {
    ltobject_structure_t *obj_structure = (ltobject_structure_t*)structure;

    ltobject_t *object = obj_structure->_objects.object_dll;
    while (object != NULL) {
        ltobject_t *next = object->_next;
        ltobject_structure_free_object(obj_structure, object);
        object = next;
    }


    for (u32 i = 0; i < sizeof(obj_structure->_sub_structures); i++) {
        if (obj_structure->_sub_structures[i]._flags.in_use) {
            obj_structure->_sub_structures[i].sub_structure->clear(obj_structure->_sub_structures[i].sub_structure);
        }
    }
}


ltcustom_structure_t *ltobject_structure_clone(const ltcustom_structure_t *structure) {
    ltobject_structure_t *obj_structure = (ltobject_structure_t*)structure;


    ltobject_structure_t *clone = (ltobject_structure_t*)malloc(sizeof(ltobject_structure_t));
    *clone = ltobject_structure_new(structure->engine);


    for (u32 i = 0; i < MAX_SUB_STRUCTURE_COUNT; i++) {
        if (obj_structure->_sub_structures[i]._flags.in_use) {
            clone->_sub_structures[i].sub_structure = obj_structure->_sub_structures[i].sub_structure->clone(obj_structure->_sub_structures[i].sub_structure);
            clone->_sub_structures[i]._flags.in_use = true;
        }
    }

    ltobject_t *object = obj_structure->_objects.object_dll;
    while (object != NULL) {
        ltobject_t *clone_object = ltobject_structure_new_object(clone, NULL);

        if (object->_flags.free) {
            object = object->_next;
            continue;
        }

        clone_object->_init = object->_init;
        clone_object->deinit = object->deinit;
        clone_object->render = object->render;
        clone_object->update = object->update;
        clone_object->clone = object->clone;
 
        ltobject_set_active(clone_object, object->_flags.active);
        ltobject_set_visible(clone_object, object->_flags.visible);

        if (object->clone == NULL) {
            clone_object->position = object->position;
            clone_object->scale = object->scale;
            clone_object->rotation = object->rotation;
            
            memcpy(&clone_object->gp, &object->gp, sizeof(object->gp));
        } else {
            clone_object->clone(object, clone_object);
        }

        object = object->_next;
    }

    clone->_structure.clear_color = obj_structure->_structure.clear_color;

    return &clone->_structure;
}
