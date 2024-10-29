#include <immintrin.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include <LTEngine/random.h>


#define RDRAND_MAX_TRIES ((u32)40)


extern bool rdrnd16_step(u16 *data);
extern bool rdrnd32_step(u32 *data);
extern bool rdrnd64_step(u64 *data);

extern const u8 dont_use_this_random_data[];
extern const u16 dont_use_this_random_data_size;


ltrandom_t ltrandom_new_custom_random(const ltcustom_random_data_t *custom_random) {
    ltrandom_t random;

    random._random_type = LTRANDOM_TYPE_CUSTOM;
    random._custom_random = *custom_random;

    random._custom_random.random_init(&random._custom_random);

    return random;
}

ltrandom_t ltrandom_new_dont_use_this_random() {
    ltrandom_t random;

    random._random_type = LTRANDOM_TYPE_DONT_USE_THIS_RANDOM;
    random._dont_use_this_random.index = 0;

    return random;
}

ltrandom_t ltrandom_new_c_random() {
    ltrandom_t random;

    random._random_type = LTRANDOM_TYPE_C_RANDOM;

    return random;
}

ltrandom_t ltrandom_new_lfsr() {
    ltrandom_t random;
    
    random._random_type = LTRANDOM_TYPE_LFSR;

    if (random._lfsr_random.state == 0) {
        random._lfsr_random.state = (rand() ^ rand());
    }

    random._lfsr_random.ticks = 0;

    return random;
}

#ifndef _WIN32
ltresult_ltrandom_t ltrandom_new_unix_random(u32 buffer_size) {
    ltrandom_t random;

    random._random_type = LTRANDOM_TYPE_UNIX_RANDOM;

    random._unix_random.random_device = fopen("/dev/urandom", "rb");

    random._unix_random.buffer = (u8*)malloc(buffer_size);
    if (fread(random._unix_random.buffer, 1, buffer_size, random._unix_random.random_device) != buffer_size) {
        // What the f**k????
        free(random._unix_random.buffer);
        return ltresult_ltrandom_new(LTRESULT_FATAL_ERR_FILE, random);
    }
    random._unix_random.buffer_size = buffer_size;
    random._unix_random.buffer_items = buffer_size;

    return ltresult_ltrandom_new(LTRESULT_SUCCESS, random);
}
#endif

ltrandom_t ltrandom_new_rdrand() {
    ltrandom_t random;

    random._random_type = LTRANDOM_TYPE_RDRAND;

    return random;
}


void ltrandom_free(ltrandom_t *random) {
    switch (random->_random_type) {
        case LTRANDOM_TYPE_CUSTOM:
            random->_custom_random.random_free(&random->_custom_random);
            break;
#ifndef _WIN32
        case LTRANDOM_TYPE_UNIX_RANDOM:
            fclose(random->_unix_random.random_device);
            break;
#endif
        default:
            break;
    }
}


void ltrandom_seed(ltrandom_t *random, u64 seed) {
    switch (random->_random_type) {
        case LTRANDOM_TYPE_DONT_USE_THIS_RANDOM:
            random->_dont_use_this_random.index = seed % dont_use_this_random_data_size;
        case LTRANDOM_TYPE_C_RANDOM:
            srand(seed);
        default:
            break;
    }
}


u8 ltrandom_get_u8(ltrandom_t *random) {
    switch (random->_random_type) {
        case LTRANDOM_TYPE_CUSTOM: {
            u8 data;
            random->_custom_random.random(&random->_custom_random, &data, sizeof(u8));
            return data;
        }

        case LTRANDOM_TYPE_DONT_USE_THIS_RANDOM:
            return dont_use_this_random_data[(random->_dont_use_this_random.index++) % dont_use_this_random_data_size];
        case LTRANDOM_TYPE_C_RANDOM:
            return (rand() ^ rand()) & 0xFF;
        case LTRANDOM_TYPE_LFSR:
            random->_lfsr_random.ticks++;

            random->_lfsr_random.state >>= 1;
            random->_lfsr_random.state |= (random->_lfsr_random.state & 1) << 7;

            if (random->_lfsr_random.ticks % 8 == 0) {
                random->_lfsr_random.state ^= (rand() ^ rand()) & 0xFF;
            }

            return random->_lfsr_random.state & 0xFF;

        case LTRANDOM_TYPE_UNIX_RANDOM:
            if (random->_unix_random.buffer_items > 0) {
                return random->_unix_random.buffer[random->_unix_random.buffer_size - (random->_unix_random.buffer_items--)];
            }
            
            if (fread(random->_unix_random.buffer, 1, random->_unix_random.buffer_size, random->_unix_random.random_device) != random->_unix_random.buffer_size) {
                // What the f**k????
                return (rand() ^ rand()) & 0xFF;
            }
            random->_unix_random.buffer_items = random->_unix_random.buffer_size;

            u8 data;
            if (fread(&data, 1, sizeof(u8), random->_unix_random.random_device) != sizeof(u8)) {
                // What the f**k????
                return (rand() ^ rand()) & 0xFF;
            }

            return data;

        case LTRANDOM_TYPE_RDRAND: {
#ifndef NO_ASM
            u8 tries = 0;
            u16 data;
            while (!rdrnd16_step(&data)) {
                // The CPU doesn't support rdrand or something else (in that case what the f**k????)
                if (++tries < RDRAND_MAX_TRIES) {
                    continue;
                }
                return (rand() ^ rand() ^ rand() ^ rand()) & 0xFF;
            }
            return data & 0xFF;
#else
            return (rand() ^ rand() ^ rand() ^ rand()) & 0xFF;
#endif
        }
        default:
            return 0;
    }
}

u16 ltrandom_get_u16(ltrandom_t *random) {
    switch (random->_random_type) {
        case LTRANDOM_TYPE_CUSTOM: {
            u16 data;
            random->_custom_random.random(&random->_custom_random, &data, sizeof(u16));
            return data;
        }

        case LTRANDOM_TYPE_C_RANDOM:
            return (rand() ^ rand()) & 0xFFFF;

#ifndef NO_ASM
        case LTRANDOM_TYPE_RDRAND: {
            u8 tries = 0;
            u16 data;
            while (!rdrnd16_step(&data)) {
                // The CPU doesn't support rdrand or something else (in that case what the f**k????)
                if (++tries < RDRAND_MAX_TRIES) {
                    continue;
                }
                return (rand() ^ rand() ^ rand() ^ rand()) & 0xFFFF;
            }
            return data;
        }
#endif
        default:
            break;
    }
    return (u16)ltrandom_get_u8(random) | ((u16)ltrandom_get_u8(random) << 8);
}

u32 ltrandom_get_u32(ltrandom_t *random) {
    switch (random->_random_type) {
        case LTRANDOM_TYPE_CUSTOM: {
            u32 data;
            random->_custom_random.random(&random->_custom_random, &data, sizeof(u32));
            return data;
        }

        case LTRANDOM_TYPE_C_RANDOM:
            return (rand() ^ rand()) & 0xFFFFFFFF;

#ifndef NO_ASM
        case LTRANDOM_TYPE_RDRAND: {
            u8 tries = 0;
            u16 data;
            while (!rdrnd16_step(&data)) {
                // The CPU doesn't support rdrand or something else (in that case what the f**k????)
                if (++tries < RDRAND_MAX_TRIES) {
                    continue;
                }
                return (rand() ^ rand() ^ rand() ^ rand()) & 0xFFFFFFFF;
            }
            return data;
        }
#endif
        default:
            break;
    }
    return (u32)ltrandom_get_u16(random) | ((u32)ltrandom_get_u16(random) << 16);
}

u64 ltrandom_get_u64(ltrandom_t *random) {
    switch (random->_random_type) {
        case LTRANDOM_TYPE_CUSTOM: {
            u64 data;
            random->_custom_random.random(&random->_custom_random, &data, sizeof(u64));
            return data;
        }

        case LTRANDOM_TYPE_C_RANDOM:
            return (rand() ^ rand()) & 0xFFFFFFFFFFFFFFFF;

#ifndef NO_ASM
        case LTRANDOM_TYPE_RDRAND: {
            u8 tries = 0;
            u16 data;
            while (!rdrnd16_step(&data)) {
                // The CPU doesn't support rdrand or something else (in that case what the f**k????)
                if (++tries < RDRAND_MAX_TRIES) {
                    continue;
                }
                return (rand() ^ rand() ^ rand() ^ rand()) & 0xFFFFFFFFFFFFFFFF;
            }
            return data;
        }
#endif
        default:
            break;
    }
    return (u64)ltrandom_get_u32(random) | ((u64)ltrandom_get_u32(random) << 32);
}


s8 ltrandom_get_s8(ltrandom_t *random) {
    return (s8)ltrandom_get_u8(random);
}

s16 ltrandom_get_s16(ltrandom_t *random) {
    return (s16)ltrandom_get_u16(random);
}

s32 ltrandom_get_s32(ltrandom_t *random) {
    return (s32)ltrandom_get_u32(random);
}

s64 ltrandom_get_s64(ltrandom_t *random) {
    return (s64)ltrandom_get_u64(random);
}


f32 ltrandom_get_f32(ltrandom_t *random) {
    return (f32)ltrandom_get_u32(random);
}

f64 ltrandom_get_f64(ltrandom_t *random) {
    return (f64)ltrandom_get_u64(random);
}


void ltrandom_get(ltrandom_t *random, void *data, u32 size) {
    for (u32 i = 0; i < size; i++) {
        ((u8*)data)[i] = ltrandom_get_u8(random);
    }
}
