#include <LTEngine/rendering/colors.h>


ltcolor_t ltcolor_new(u8 r, u8 g, u8 b) {
    ltcolor_t color;
    color.r = r;
    color.g = g;
    color.b = b;
    return color;
}


ltcolor_t ltcolor_add(ltcolor_t a, ltcolor_t b) {
    return ltcolor_new(
        a.r + b.r,
        a.g + b.g,
        a.b + b.b
    );
}

ltcolor_t ltcolor_sub(ltcolor_t a, ltcolor_t b) {
    return ltcolor_new(
        a.r - b.r,
        a.g - b.g,
        a.b - b.b
    );
}

ltcolor_t ltcolor_mul(ltcolor_t a, ltcolor_t b) {
    return ltcolor_new(
        a.r * b.r,
        a.g * b.g,
        a.b * b.b
    );
}

ltcolor_t ltcolor_div(ltcolor_t a, ltcolor_t b) {
    return ltcolor_new(
        a.r / b.r,
        a.g / b.g,
        a.b / b.b
    );
}

ltcolor_t ltcolor_addf(ltcolor_t a, f32 b) {
    return ltcolor_new(
        a.r + b,
        a.g + b,
        a.b + b
    );
}

ltcolor_t ltcolor_subf(ltcolor_t a, f32 b) {
    return ltcolor_new(
        a.r - b,
        a.g - b,
        a.b - b
    );
}

ltcolor_t ltcolor_mulf(ltcolor_t a, f32 b) {
    return ltcolor_new(
        a.r * b,
        a.g * b,
        a.b * b
    );
}

ltcolor_t ltcolor_divf(ltcolor_t a, f32 b) {
    return ltcolor_new(
        a.r / b,
        a.g / b,
        a.b / b
    );
}

ltcolor_t ltcolor_mix(ltcolor_t a, ltcolor_t b) {
    return ltcolor_new(
        (u16)a.r * b.r / 255,
        (u16)a.g * b.g / 255,
        (u16)a.b * b.b / 255
    );
}


ltcolora_t ltcolora_new(u8 r, u8 g, u8 b, u8 a) {
    ltcolora_t color;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
    return color;
}


ltcolora_t ltcolora_add(ltcolora_t a, ltcolora_t b) {
    return ltcolora_new(
        a.r + b.r,
        a.g + b.g,
        a.b + b.b,
        a.a + b.a
    );
}

ltcolora_t ltcolora_sub(ltcolora_t a, ltcolora_t b) {
    return ltcolora_new(
        a.r - b.r,
        a.g - b.g,
        a.b - b.b,
        a.a - b.a
    );
}

ltcolora_t ltcolora_mul(ltcolora_t a, ltcolora_t b) {
    return ltcolora_new(
        a.r * b.r,
        a.g * b.g,
        a.b * b.b,
        a.a * b.a
    );
}

ltcolora_t ltcolora_div(ltcolora_t a, ltcolora_t b) {
    return ltcolora_new(
        a.r / b.r,
        a.g / b.g,
        a.b / b.b,
        a.a / b.a
    );
}

ltcolora_t ltcolora_addf(ltcolora_t a, f32 b) {
    return ltcolora_new(
        a.r + b,
        a.g + b,
        a.b + b,
        a.a + b
    );
}

ltcolora_t ltcolora_subf(ltcolora_t a, f32 b) {
    return ltcolora_new(
        a.r - b,
        a.g - b,
        a.b - b,
        a.a - b
    );
}

ltcolora_t ltcolora_mulf(ltcolora_t a, f32 b) {
    return ltcolora_new(
        a.r * b,
        a.g * b,
        a.b * b,
        a.a * b
    );
}

ltcolora_t ltcolora_divf(ltcolora_t a, f32 b) {
    return ltcolora_new(
        a.r / b,
        a.g / b,
        a.b / b,
        a.a / b
    );
}

ltcolora_t ltcolora_mix(ltcolora_t a, ltcolora_t b) {
    return ltcolora_new(
        (u16)a.r * b.r / 255,
        (u16)a.g * b.g / 255,
        (u16)a.b * b.b / 255,
        (u16)a.a * b.a / 255
    );
}


ltcolor_t ltcolor_fromA(ltcolora_t color) {
    return ltcolor_new(color.r, color.g, color.b);
}

ltcolora_t ltcolora_from(ltcolor_t color) {
    return ltcolora_new(color.r, color.g, color.b, 255);
}
