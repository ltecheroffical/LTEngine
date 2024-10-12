#include <LTEngine/math/rect.h>


ltrect_t ltrect_new(f32 x, f32 y, f32 w, f32 h) {
    return (ltrect_t){x, y, w, h};
}

ltrect_t ltrect_add(ltrect_t a, ltrect_t b) {
    return (ltrect_t){
        a.x + b.x,
        a.y + b.y,
        a.w + b.w,
        a.h + b.h
    };
}

ltrect_t ltrect_sub(ltrect_t a, ltrect_t b) {
    return (ltrect_t){
        a.x - b.x,
        a.y - b.y,
        a.w - b.w,
        a.h - b.h
    };
}

ltrect_t ltrect_mul(ltrect_t a, ltrect_t b) {
    return (ltrect_t){
        a.x * b.x,
        a.y * b.y,
        a.w * b.w,
        a.h * b.h
    };
}

ltrect_t ltrect_div(ltrect_t a, ltrect_t b) {
    return (ltrect_t){
        a.x / b.x,
        a.y / b.y,
        a.w / b.w,
        a.h / b.h
    };
}

ltrect_t ltrect_addf(ltrect_t a, f32 b) {
    return (ltrect_t){
        a.x + b,
        a.y + b,
        a.w + b,
        a.h + b
    };
}

ltrect_t ltrect_subf(ltrect_t a, f32 b) {
    return (ltrect_t){
        a.x - b,
        a.y - b,
        a.w - b,
        a.h - b
    };
}

ltrect_t ltrect_mulf(ltrect_t a, f32 b) {
    return (ltrect_t){
        a.x * b,
        a.y * b,
        a.w * b,
        a.h * b
    };
}

ltrect_t ltrect_divf(ltrect_t a, f32 b) {
    return (ltrect_t){
        a.x / b,
        a.y / b,
        a.w / b,
        a.h / b
    };
}




ltrecti_t ltrecti_new(i32 x, i32 y, i32 w, i32 h) {
    return (ltrecti_t){x, y, w, h};
}


ltrecti_t ltrecti_add(ltrecti_t a, ltrecti_t b) {
    return (ltrecti_t){
        a.x + b.x,
        a.y + b.y,
        a.w + b.w,
        a.h + b.h
    };
}

ltrecti_t ltrecti_sub(ltrecti_t a, ltrecti_t b) {
    return (ltrecti_t){
        a.x - b.x,
        a.y - b.y,
        a.w - b.w,
        a.h - b.h
    };
}

ltrecti_t ltrecti_mul(ltrecti_t a, ltrecti_t b) {
    return (ltrecti_t){
        a.x * b.x,
        a.y * b.y,
        a.w * b.w,
        a.h * b.h
    };
}

ltrecti_t ltrecti_div(ltrecti_t a, ltrecti_t b) {
    return (ltrecti_t){
        a.x / b.x,
        a.y / b.y,
        a.w / b.w,
        a.h / b.h
    };
}

ltrecti_t ltrecti_addi(ltrecti_t a, i32 b) {
    return (ltrecti_t){
        a.x + b,
        a.y + b,
        a.w + b,
        a.h + b
    };
}

ltrecti_t ltrecti_subi(ltrecti_t a, i32 b) {
    return (ltrecti_t){
        a.x - b,
        a.y - b,
        a.w - b,
        a.h - b
    };
}

ltrecti_t ltrecti_muli(ltrecti_t a, i32 b) {
    return (ltrecti_t){
        a.x * b,
        a.y * b,
        a.w * b,
        a.h * b
    };
}

ltrecti_t ltrecti_divi(ltrecti_t a, i32 b) {
    return (ltrecti_t){
        a.x / b,
        a.y / b,
        a.w / b,
        a.h / b
    };
}




ltrectu_t ltrectu_new() {
    return (ltrectu_t){0, 0, 0, 0};
}

ltrectu_t ltrectu_new_with_values(u32 x, u32 y, u32 w, u32 h) {
    return (ltrectu_t){x, y, w, h};
}


ltrectu_t ltrectu_add(ltrectu_t a, ltrectu_t b) {
    return (ltrectu_t){
        a.x + b.x,
        a.y + b.y,
        a.w + b.w,
        a.h + b.h
    };
}

ltrectu_t ltrectu_sub(ltrectu_t a, ltrectu_t b) {
    return (ltrectu_t){
        a.x - b.x,
        a.y - b.y,
        a.w - b.w,
        a.h - b.h
    };
}

ltrectu_t ltrectu_mul(ltrectu_t a, ltrectu_t b) {
    return (ltrectu_t){
        a.x * b.x,
        a.y * b.y,
        a.w * b.w,
        a.h * b.h
    };
}

ltrectu_t ltrectu_div(ltrectu_t a, ltrectu_t b) {
    return (ltrectu_t){
        a.x / b.x,
        a.y / b.y,
        a.w / b.w,
        a.h / b.h
    };
}


ltrectu_t ltrectu_addu(ltrectu_t a, u32 b) {
    return (ltrectu_t){
        a.x + b,
        a.y + b,
        a.w + b,
        a.h + b
    };
}

ltrectu_t ltrectu_subu(ltrectu_t a, u32 b) {
    return (ltrectu_t){
        a.x - b,
        a.y - b,
        a.w - b,
        a.h - b
    };
}

ltrectu_t ltrectu_mulu(ltrectu_t a, u32 b) {
    return (ltrectu_t){
        a.x * b,
        a.y * b,
        a.w * b,
        a.h * b
    };
}

ltrectu_t ltrectu_divu(ltrectu_t a, u32 b) {
    return (ltrectu_t){
        a.x / b,
        a.y / b,
        a.w / b,
        a.h / b
    };
}
