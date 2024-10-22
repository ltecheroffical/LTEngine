#pragma once

#include <LTEngine/engine.h>

#include <LTEngine/math/vec2.h>


#define MAX_SUB_STRUCTURE_COUNT ((u32)16)


typedef struct ltobject_structure_t {
    ltcustom_structure_t _structure;

    struct {
        struct ltobject_t {
            struct ltobject_t *_next;
            struct ltobject_t *_prev;

            struct ltobject_structure_t *_structure;


            ltvec2_t position;
            ltvec2_t scale;
            f32 rotation;

            union {
                u64 u64;
                u32 u32[2];
                u16 u16[4];
                u8 u8[8];

                s64 i64;
                s32 i32[2];
                s16 i16[4];
                s8 i8[8];

                f32 f32[2];
                f64 f64;

                bool bool[8];

                void *ptr;
                const void *const_ptr;
            } gp[20];

            struct {
                bool visible:1;
                bool active:1;
                
                bool free:1;
            } _flags;

            void (*_init)(struct ltobject_t *object);
            void (*update)(struct ltobject_t *object, f32 delta);
            void (*render)(struct ltobject_t *object, ltrenderer_t *renderer);
            void (*deinit)(struct ltobject_t *object);

            void (*clone)(const struct ltobject_t *object, struct ltobject_t *clone);
        } *object_dll;
        u32 count;
    } _objects;

    struct {
        struct {
            bool in_use:1;
        } _flags;
        ltcustom_structure_t *sub_structure;
    } _sub_structures[MAX_SUB_STRUCTURE_COUNT];
} ltobject_structure_t;

typedef struct ltobject_t ltobject_t;


ltobject_structure_t ltobject_structure_new(ltengine_t *engine);

u32 ltobject_structure_add_sub_structure(ltobject_structure_t *structure, ltcustom_structure_t *sub_structure);
void ltobject_structure_remove_sub_structure(ltobject_structure_t *structure, u32 index);
void ltobject_structure_clear_substructure(ltobject_structure_t *structure, u32 index);
ltcustom_structure_t *ltobject_structure_get_sub_structure(ltobject_structure_t *structure, u32 index);

void ltobject_structure_set_clear_color(ltobject_structure_t *structure, ltcolor_t color);

ltobject_t *ltobject_structure_new_object(ltobject_structure_t *structure, void (*init)(ltobject_t *object));
void ltobject_structure_free_object(ltobject_structure_t *structure, ltobject_t *object);


ltobject_t *ltobject_next(ltobject_t *object);
ltobject_t *ltobject_prev(ltobject_t *object);

ltobject_structure_t *ltobject_get_structure(ltobject_t *object);
ltengine_t *ltobject_get_engine(ltobject_t *object);

void ltobject_set_active(ltobject_t *object, bool active);
void ltobject_set_visible(ltobject_t *object, bool visible);
