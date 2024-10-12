#include <math.h>

#include <LTEngine/math/vec2.h>


ltvec2_t ltvec2_new(f32 x, f32 y) {
    return (ltvec2_t){x, y};
}


ltvec2_t ltvec2_add(ltvec2_t a, ltvec2_t b) {
    return (ltvec2_t){a.x + b.x, a.y + b.y};
}

ltvec2_t ltvec2_sub(ltvec2_t a, ltvec2_t b) {
    return (ltvec2_t){a.x - b.x, a.y - b.y};
}

ltvec2_t ltvec2_mul(ltvec2_t a, ltvec2_t b) {
    return (ltvec2_t){a.x * b.x, a.y * b.y};
}

ltvec2_t ltvec2_div(ltvec2_t a, ltvec2_t b) {
    return (ltvec2_t){a.x / b.x, a.y / b.y};
}

ltvec2_t ltvec2_addf(ltvec2_t a, f32 b) {
    return (ltvec2_t){a.x + b, a.y + b};
}

ltvec2_t ltvec2_subf(ltvec2_t a, f32 b) {
    return (ltvec2_t){a.x - b, a.y - b};
}

ltvec2_t ltvec2_mulf(ltvec2_t a, f32 b) {
    return (ltvec2_t){a.x * b, a.y * b};
}

ltvec2_t ltvec2_divf(ltvec2_t a, f32 b) {
    return (ltvec2_t){a.x / b, a.y / b};
}

ltvec2_t ltvec2_normalize(ltvec2_t a) {
    f32 mag = sqrtf(a.x * a.x + a.y * a.y);
    return (ltvec2_t){a.x / mag, a.y / mag };
}




ltvec2i_t ltvec2i_new(i32 x, i32 y) {
    return (ltvec2i_t){x, y};
}


ltvec2i_t ltvec2i_add(ltvec2i_t a, ltvec2i_t b) {
    return (ltvec2i_t){a.x + b.x, a.y + b.y};
}

ltvec2i_t ltvec2i_sub(ltvec2i_t a, ltvec2i_t b) {
    return (ltvec2i_t){a.x - b.x, a.y - b.y};
}

ltvec2i_t ltvec2i_mul(ltvec2i_t a, ltvec2i_t b) {
    return (ltvec2i_t){a.x * b.x, a.y * b.y};
}

ltvec2i_t ltvec2i_div(ltvec2i_t a, ltvec2i_t b) {
    return (ltvec2i_t){a.x / b.x, a.y / b.y};
}


ltvec2i_t ltvec2i_addi(ltvec2i_t a, i32 b) {
    return (ltvec2i_t){a.x + b, a.y + b};
}

ltvec2i_t ltvec2i_subi(ltvec2i_t a, i32 b) {
    return (ltvec2i_t){a.x - b, a.y - b};
}

ltvec2i_t ltvec2i_muli(ltvec2i_t a, i32 b) {
    return (ltvec2i_t){a.x * b, a.y * b};
}

ltvec2i_t ltvec2i_divi(ltvec2i_t a, i32 b) {
    return (ltvec2i_t){a.x / b, a.y / b};
}




ltvec2u_t ltvec2u_new(u32 x, u32 y) {
    return (ltvec2u_t){x, y};
}


ltvec2u_t ltvec2u_add(ltvec2u_t a, ltvec2u_t b) {
    return (ltvec2u_t){a.x + b.x, a.y + b.y};
}

ltvec2u_t ltvec2u_sub(ltvec2u_t a, ltvec2u_t b) {
    return (ltvec2u_t){a.x - b.x, a.y - b.y};
}

ltvec2u_t ltvec2u_mul(ltvec2u_t a, ltvec2u_t b) {
    return (ltvec2u_t){a.x * b.x, a.y * b.y};
}

ltvec2u_t ltvec2u_div(ltvec2u_t a, ltvec2u_t b) {
    return (ltvec2u_t){a.x / b.x, a.y / b.y};
}

ltvec2u_t ltvec2u_addu(ltvec2u_t a, u32 b) {
    return (ltvec2u_t){a.x + b, a.y + b};
}

ltvec2u_t ltvec2u_subu(ltvec2u_t a, u32 b) {
    return (ltvec2u_t){a.x - b, a.y - b};
}

ltvec2u_t ltvec2u_mulu(ltvec2u_t a, u32 b) {
    return (ltvec2u_t){a.x * b, a.y * b};
}

ltvec2u_t ltvec2u_divu(ltvec2u_t a, u32 b) {
    return (ltvec2u_t){a.x / b, a.y / b};
}
