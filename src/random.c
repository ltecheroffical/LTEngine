#include <immintrin.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include <LTEngine/random.h>


#define RDRAND_MAX_TRIES ((u32)40)


ltrandom_t ltrandom_new_custom_random(const ltcustom_random_data_t *custom_random) {
    ltrandom_t random;

    random.random_type = LTRANDOM_TYPE_CUSTOM;
    random.custom_random = *custom_random;

    random.custom_random.random_init(&random.custom_random);

    return random;
}

ltrandom_t ltrandom_new_c_random() {
    ltrandom_t random;

    random.random_type = LTRANDOM_TYPE_C_RANDOM;

    return random;
}

ltrandom_t ltrandom_new_lfsr() {
    ltrandom_t random;
    
    random.random_type = LTRANDOM_TYPE_LFSR;

    if (random.lfsr_random.state == 0) {
        random.lfsr_random.state = (rand() ^ rand());
    }

    random.lfsr_random.ticks = 0;

    return random;
}

#ifndef _WIN32
ltrandom_t ltrandom_new_unix_random(u32 buffer_size) {
    ltrandom_t random;

    random.random_type = LTRANDOM_TYPE_UNIX_RANDOM;

    random.unix_random.random_device = fopen("/dev/urandom", "rb");

    random.unix_random.buffer = (u8*)malloc(buffer_size);
    if (fread(random.unix_random.buffer, 1, buffer_size, random.unix_random.random_device) != buffer_size) {
        // What the f**k????
        free(random.unix_random.buffer);
        return ltrandom_new_c_random();
    }
    random.unix_random.buffer_size = buffer_size;
    random.unix_random.buffer_items = buffer_size;

    return random;
}
#endif

ltrandom_t ltrandom_new_rdrand() {
    ltrandom_t random;

    random.random_type = LTRANDOM_TYPE_RDRAND;

    return random;
}


void ltrandom_free(ltrandom_t *random) {
    switch (random->random_type) {
        case LTRANDOM_TYPE_CUSTOM:
            random->custom_random.random_free(&random->custom_random);
            break;
#ifndef _WIN32
        case LTRANDOM_TYPE_UNIX_RANDOM:
            fclose(random->unix_random.random_device);
            break;
#endif
        default:
            break;
    }
}


u8 ltrandom_get_u8(ltrandom_t *random) {
    switch (random->random_type) {
        case LTRANDOM_TYPE_CUSTOM: {
            u8 data;
            random->custom_random.random(&random->custom_random, &data, sizeof(u8));
            return data;
        }

        case LTRANDOM_TYPE_C_RANDOM:
            return (rand() ^ rand()) & 0xFF;
        case LTRANDOM_TYPE_LFSR:
            random->lfsr_random.ticks++;

            random->lfsr_random.state >>= 1;
            random->lfsr_random.state |= (random->lfsr_random.state & 1) << 7;

            if (random->lfsr_random.ticks % 4 == 0) {
#ifndef _WIN32
                random->lfsr_random.state ^= getpid();
#else
                // Vaguely put here with guidance from the Microsoft docs
                random->lfsr_random.state ^= (u32)GetCurrentProcessId();
#endif
            }

            if (random->lfsr_random.ticks % 8 == 0) {
                random->lfsr_random.state ^= (rand() ^ rand()) & 0xFF;
            }

            return random->lfsr_random.state & 0xFF;

        case LTRANDOM_TYPE_UNIX_RANDOM:
            if (random->unix_random.buffer_items > 0) {
                return random->unix_random.buffer[random->unix_random.buffer_size - (random->unix_random.buffer_items--)];
            }
            
            if (fread(random->unix_random.buffer, 1, random->unix_random.buffer_size, random->unix_random.random_device) != random->unix_random.buffer_size) {
                // What the f**k????
                return (rand() ^ rand()) & 0xFF;
            }
            random->unix_random.buffer_items = random->unix_random.buffer_size;

            u8 data;
            if (fread(&data, 1, sizeof(u8), random->unix_random.random_device) != sizeof(u8)) {
                // What the f**k????
                return (rand() ^ rand()) & 0xFF;
            }

            return data;

        case LTRANDOM_TYPE_RDRAND: {
            u8 tries = 0;
            u16 data;
            while (!_rdrand16_step(&data)) {
                // The CPU doesn't support rdrand or something else (in that case what the f**k????)
                if (++tries < RDRAND_MAX_TRIES) {
                    continue;
                }
                return (rand() ^ rand() ^ rand() ^ rand()) & 0xFF;
            }
            return data & 0xFF;
        }
        default:
            return 0;
    }
}

u16 ltrandom_get_u16(ltrandom_t *random) {
    if (random->random_type == LTRANDOM_TYPE_CUSTOM) {
        u16 data;
        random->custom_random.random(&random->custom_random, &data, sizeof(u16));
        return data;
    } else if (random->random_type == LTRANDOM_TYPE_RDRAND) {
        u8 tries = 0;
        u16 data;
        while (!_rdrand16_step(&data)) {
            // The CPU doesn't support rdrand or something else (in that case what the f**k????)
            if (++tries < RDRAND_MAX_TRIES) {
                continue;
            }
            return (rand() ^ rand() ^ rand() ^ rand()) & 0xFFFF;
        }
        return data;
    }
    return (u16)ltrandom_get_u8(random) | ((u16)ltrandom_get_u8(random) << 8);
}

u32 ltrandom_get_u32(ltrandom_t *random) {
    if (random->random_type == LTRANDOM_TYPE_CUSTOM) {
        u32 data;
        random->custom_random.random(&random->custom_random, &data, sizeof(u32));
        return data;
    } else if (random->random_type == LTRANDOM_TYPE_RDRAND) {
        u8 tries = 0;
        u32 data;
        while (!_rdrand32_step(&data)) {
            // The CPU doesn't support rdrand or something else (in that case what the f**k????)
            if (++tries < RDRAND_MAX_TRIES) {
                continue;
            }
            return (rand() ^ rand() ^ rand() ^ rand()) & 0xFFFF;
        }
        return data;
    }
    return (u32)ltrandom_get_u16(random) | ((u32)ltrandom_get_u16(random) << 16);
}

u64 ltrandom_get_u64(ltrandom_t *random) {
    if (random->random_type == LTRANDOM_TYPE_CUSTOM) {
        u64 data;
        random->custom_random.random(&random->custom_random, &data, sizeof(u64));
        return data;
    } else if (random->random_type == LTRANDOM_TYPE_RDRAND) {
        u8 tries = 0;
        u64 data;
        while (!_rdrand64_step(&data)) {
            // The CPU doesn't support rdrand or something else (in that case what the f**k????)
            if (++tries < RDRAND_MAX_TRIES) {
                continue;
            }
            return (rand() ^ rand() ^ rand() ^ rand()) & 0xFFFF;
        }
        return data;
    }
    return (u64)ltrandom_get_u32(random) | ((u64)ltrandom_get_u32(random) << 32);
}


i8 ltrandom_get_i8(ltrandom_t *random) {
    return (i8)ltrandom_get_u8(random);
}

i16 ltrandom_get_i16(ltrandom_t *random) {
    return (i16)ltrandom_get_u16(random);
}

i32 ltrandom_get_i32(ltrandom_t *random) {
    return (i32)ltrandom_get_u32(random);
}

i64 ltrandom_get_i64(ltrandom_t *random) {
    return (i64)ltrandom_get_u64(random);
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
