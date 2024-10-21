#pragma once

#include <stdio.h>

#include <LTEngine/common/types/inttypes.h>
#include <LTEngine/common/types/floattypes.h>
#include <LTEngine/common/types/booltypes.h>


typedef struct {
    union {
        struct ltcustom_random_data_t {
            union {
                u64 u64;
                u32 u32[2];
                u16 u16[4];
                u8 u8[8];

                i64 i64;
                i32 i32[2];
                i16 i16[4];
                i8 i8[8];

                f64 f64;
                f32 f32[2];

                void *ptr;
                const void *const_ptr;
            } data[20];

            void (*random_init)(struct ltcustom_random_data_t *random);
            void (*random)(struct ltcustom_random_data_t *random, void *output, u32 size);
            void (*random_free)(struct ltcustom_random_data_t *random);
        } custom_random;

        struct {
            u64 state;
            u32 ticks;
        } lfsr_random;
        struct {
            u8 *buffer;
            u32 buffer_size;
            u32 buffer_items;

            FILE *random_device;
        } unix_random;
    };

    enum ltrandom_type_t { // Lowest security to highest security
        LTRANDOM_TYPE_CUSTOM = 0, // Can't determine security

        LTRANDOM_TYPE_C_RANDOM,
        LTRANDOM_TYPE_LFSR,

#ifndef _WIN32
        LTRANDOM_TYPE_UNIX_RANDOM,
#endif
        LTRANDOM_TYPE_RDRAND,
    } random_type;
} ltrandom_t;

typedef struct ltcustom_random_data_t ltcustom_random_data_t;

ltrandom_t ltrandom_new_custom_random(const ltcustom_random_data_t *custom_random);
ltrandom_t ltrandom_new_c_random();
ltrandom_t ltrandom_new_lfsr();
ltrandom_t ltrandom_new_unix_random(u32 buffer_size);
ltrandom_t ltrandom_new_rdrand();

void ltrandom_free(ltrandom_t *random);

u8 ltrandom_get_u8(ltrandom_t *random);
u16 ltrandom_get_u16(ltrandom_t *random);
u32 ltrandom_get_u32(ltrandom_t *random);
u64 ltrandom_get_u64(ltrandom_t *random);

i8 ltrandom_get_i8(ltrandom_t *random);
i16 ltrandom_get_i16(ltrandom_t *random);
i32 ltrandom_get_i32(ltrandom_t *random);
i64 ltrandom_get_i64(ltrandom_t *random);

f32 ltrandom_get_f32(ltrandom_t *random);
f64 ltrandom_get_f64(ltrandom_t *random);

void ltrandom_get(ltrandom_t *random, void *data, u32 size);
