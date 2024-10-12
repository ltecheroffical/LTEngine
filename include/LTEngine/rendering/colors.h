#include <LTEngine/common/types/inttypes.h>
#include <LTEngine/common/types/floattypes.h>


#ifndef _LTCOLOR_H_
#define _LTCOLOR_H_

#pragma pack(1)

typedef struct {
    u8 r, g, b;
} ltcolor_t;

ltcolor_t ltcolor_new(u8 r, u8 g, u8 b);

ltcolor_t ltcolor_add(ltcolor_t a, ltcolor_t b);
ltcolor_t ltcolor_sub(ltcolor_t a, ltcolor_t b);
ltcolor_t ltcolor_mul(ltcolor_t a, ltcolor_t b);
ltcolor_t ltcolor_div(ltcolor_t a, ltcolor_t b);
ltcolor_t ltcolor_addf(ltcolor_t a, f32 b);
ltcolor_t ltcolor_subf(ltcolor_t a, f32 b);
ltcolor_t ltcolor_mulf(ltcolor_t a, f32 b);
ltcolor_t ltcolor_divf(ltcolor_t a, f32 b);
ltcolor_t ltcolor_mix(ltcolor_t a, ltcolor_t b);


typedef struct {
    u8 r, g, b, a;
} ltcolora_t;

ltcolora_t ltcolora_new(u8 r, u8 g, u8 b, u8 a);

ltcolora_t ltcolora_add(ltcolora_t a, ltcolora_t b);
ltcolora_t ltcolora_sub(ltcolora_t a, ltcolora_t b);
ltcolora_t ltcolora_mul(ltcolora_t a, ltcolora_t b);
ltcolora_t ltcolora_div(ltcolora_t a, ltcolora_t b);
ltcolora_t ltcolora_addf(ltcolora_t a, f32 b);
ltcolora_t ltcolora_subf(ltcolora_t a, f32 b);
ltcolora_t ltcolora_mulf(ltcolora_t a, f32 b);
ltcolora_t ltcolora_divf(ltcolora_t a, f32 b);
ltcolora_t ltcolora_mix(ltcolora_t a, ltcolora_t b);

ltcolora_t ltcolora_from(ltcolor_t color);
ltcolor_t ltcolor_fromA(ltcolora_t colora);


static const ltcolor_t LTCOLOR_BLACK = {0, 0, 0};
static const ltcolor_t LTCOLOR_WHITE = {255, 255, 255};
static const ltcolor_t LTCOLOR_RED = {255, 0, 0};
static const ltcolor_t LTCOLOR_GREEN = {0, 255, 0};
static const ltcolor_t LTCOLOR_BLUE = {0, 0, 255};
static const ltcolor_t LTCOLOR_YELLOW = {255, 255, 0};
static const ltcolor_t LTCOLOR_PURPLE = {255, 0, 255};
static const ltcolor_t LTCOLOR_CYAN = {0, 255, 255};
static const ltcolor_t LTCOLOR_GRAY = {128, 128, 128};

static const ltcolora_t LTCOLORA_BLACK = {0, 0, 0, 255};
static const ltcolora_t LTCOLORA_WHITE = {255, 255, 255, 255};
static const ltcolora_t LTCOLORA_RED = {255, 0, 0, 255};
static const ltcolora_t LTCOLORA_GREEN = {0, 255, 0, 255};
static const ltcolora_t LTCOLORA_BLUE = {0, 0, 255, 255};
static const ltcolora_t LTCOLORA_YELLOW = {255, 255, 0, 255};
static const ltcolora_t LTCOLORA_PURPLE = {255, 0, 255, 255};
static const ltcolora_t LTCOLORA_CYAN = {0, 255, 255, 255};
static const ltcolora_t LTCOLORA_GRAY = {128, 128, 128, 255};
static const ltcolora_t LTCOLORA_CLEAR = {0, 0, 0, 0};


#pragma pack()

#endif
