#include <LTEngine/common/types/floattypes.h>
#include <LTEngine/common/types/inttypes.h>

#ifndef _LTRECT_H_
#define _LTRECT_H_

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(1)

typedef struct {
    f32 x, y;
    f32 w, h;
} ltrect_t;

ltrect_t ltrect_new(f32 x, f32 y, f32 w, f32 h);

ltrect_t ltrect_add(ltrect_t a, ltrect_t b);
ltrect_t ltrect_sub(ltrect_t a, ltrect_t b);
ltrect_t ltrect_mul(ltrect_t a, ltrect_t b);
ltrect_t ltrect_div(ltrect_t a, ltrect_t b);
ltrect_t ltrect_addf(ltrect_t a, f32 b);
ltrect_t ltrect_subf(ltrect_t a, f32 b);
ltrect_t ltrect_mulf(ltrect_t a, f32 b);
ltrect_t ltrect_divf(ltrect_t a, f32 b);


typedef struct {
    s32 x, y;
    s32 w, h;
} ltrecti_t;

ltrecti_t ltrecti_new(s32 x, s32 y, s32 w, s32 h);

ltrecti_t ltrecti_add(ltrecti_t a, ltrecti_t b);
ltrecti_t ltrecti_sub(ltrecti_t a, ltrecti_t b);
ltrecti_t ltrecti_mul(ltrecti_t a, ltrecti_t b);
ltrecti_t ltrecti_div(ltrecti_t a, ltrecti_t b);
ltrecti_t ltrecti_addi(ltrecti_t a, s32 b);
ltrecti_t ltrecti_subi(ltrecti_t a, s32 b);
ltrecti_t ltrecti_muli(ltrecti_t a, s32 b);
ltrecti_t ltrecti_divi(ltrecti_t a, s32 b);


typedef struct {
    u32 x, y;
    u32 w, h;
} ltrectu_t;

ltrectu_t ltrectu_new();
ltrectu_t ltrectu_new_with_values(u32 x, u32 y, u32 w, u32 h);

ltrectu_t ltrectu_add(ltrectu_t a, ltrectu_t b);
ltrectu_t ltrectu_sub(ltrectu_t a, ltrectu_t b);
ltrectu_t ltrectu_mul(ltrectu_t a, ltrectu_t b);
ltrectu_t ltrectu_div(ltrectu_t a, ltrectu_t b);
ltrectu_t ltrectu_addu(ltrectu_t a, u32 b);
ltrectu_t ltrectu_subu(ltrectu_t a, u32 b);
ltrectu_t ltrectu_mulu(ltrectu_t a, u32 b);
ltrectu_t ltrectu_divu(ltrectu_t a, u32 b);

#pragma pack()


static const ltrect_t LTRECT_ZERO = {0.f, 0.f, 0.f, 0.f};
static const ltrecti_t LTRECTI_ZERO = {0, 0, 0, 0};
static const ltrectu_t LTRECTU_ZERO = {0, 0, 0, 0};


#ifdef __cplusplus
}
#endif
#endif
