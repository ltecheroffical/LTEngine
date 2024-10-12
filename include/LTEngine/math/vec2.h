#include <LTEngine/common/types/floattypes.h>
#include <LTEngine/common/types/inttypes.h>

#ifndef _LTVEC2_H_
#define _LTVEC2_H_

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(1)

typedef struct {
    f32 x, y;
} ltvec2_t;

ltvec2_t ltvec2_new(f32 x, f32 y);

ltvec2_t ltvec2_add(ltvec2_t a, ltvec2_t b);
ltvec2_t ltvec2_sub(ltvec2_t a, ltvec2_t b);
ltvec2_t ltvec2_mul(ltvec2_t a, ltvec2_t b);
ltvec2_t ltvec2_div(ltvec2_t a, ltvec2_t b);
ltvec2_t ltvec2_addf(ltvec2_t a, f32 b);
ltvec2_t ltvec2_subf(ltvec2_t a, f32 b);
ltvec2_t ltvec2_mulf(ltvec2_t a, f32 b);
ltvec2_t ltvec2_divf(ltvec2_t a, f32 b);
ltvec2_t ltvec2_normalize(ltvec2_t a);


typedef struct {
    i32 x, y;
} ltvec2i_t;

ltvec2i_t ltvec2i_new(i32 x, i32 y);

ltvec2i_t ltvec2i_add(ltvec2i_t a, ltvec2i_t b);
ltvec2i_t ltvec2i_sub(ltvec2i_t a, ltvec2i_t b);
ltvec2i_t ltvec2i_mul(ltvec2i_t a, ltvec2i_t b);
ltvec2i_t ltvec2i_div(ltvec2i_t a, ltvec2i_t b);
ltvec2i_t ltvec2i_addi(ltvec2i_t a, i32 b);
ltvec2i_t ltvec2i_subi(ltvec2i_t a, i32 b);
ltvec2i_t ltvec2i_muli(ltvec2i_t a, i32 b);
ltvec2i_t ltvec2i_divi(ltvec2i_t a, i32 b);
ltvec2i_t ltvec2i_normalize(ltvec2i_t a);


typedef struct {
    u32 x, y;
} ltvec2u_t;

ltvec2u_t ltvec2u_new(u32 x, u32 y);

ltvec2u_t ltvec2u_add(ltvec2u_t a, ltvec2u_t b);
ltvec2u_t ltvec2u_sub(ltvec2u_t a, ltvec2u_t b);
ltvec2u_t ltvec2u_mul(ltvec2u_t a, ltvec2u_t b);
ltvec2u_t ltvec2u_div(ltvec2u_t a, ltvec2u_t b);
ltvec2u_t ltvec2u_addu(ltvec2u_t a, u32 b);
ltvec2u_t ltvec2u_subu(ltvec2u_t a, u32 b);
ltvec2u_t ltvec2u_mulu(ltvec2u_t a, u32 b);
ltvec2u_t ltvec2u_divu(ltvec2u_t a, u32 b);
ltvec2u_t ltvec2u_normalize(ltvec2u_t a);


static const ltvec2_t LTVEC2_ZERO = {0.f, 0.f};
static const ltvec2_t LTVEC2_ONE = {1.f, 1.f};
static const ltvec2_t LTVEC2_UP = {0.f, 1.f};
static const ltvec2_t LTVEC2_DOWN = {0.f, -1.f};
static const ltvec2_t LTVEC2_LEFT = {-1.f, 0.f};
static const ltvec2_t LTVEC2_RIGHT = {1.f, 0.f};

static const ltvec2i_t LTVEC2I_ZERO = {0, 0};
static const ltvec2i_t LTVEC2I_ONE = {1, 1};
static const ltvec2i_t LTVEC2I_UP = {0, 1};
static const ltvec2i_t LTVEC2I_DOWN = {0, -1};
static const ltvec2i_t LTVEC2I_LEFT = {-1, 0};
static const ltvec2i_t LTVEC2I_RIGHT = {1, 0};

static const ltvec2u_t LTVEC2U_ZERO = {0, 0};
static const ltvec2u_t LTVEC2U_ONE = {1, 1};
/* No directions with ltvec2u_t because it uses u32 */

#pragma pack()

#ifdef __cplusplus
}
#endif
#endif
