#pragma once

#include <LTEngine/common/types/inttypes.h>


namespace LTEngine::Rendering {
    typedef struct ltcolor_t {
        u8 r, g, b;

        ltcolor_t(u8 r, u8 g, u8 b) : r(r), g(g), b(b) {}

        ltcolor_t operator+(ltcolor_t other) {
            return ltcolor_t(this->r + other.r, this->g + other.g, this->b + other.b);
        }

        ltcolor_t operator+(u8 other) {
            return ltcolor_t(this->r + other, this->g + other, this->b + other);
        }

        ltcolor_t operator-(ltcolor_t other) {
            return ltcolor_t(this->r - other.r, this->g - other.g, this->b - other.b);
        }

        ltcolor_t operator-(u8 other) {
            return ltcolor_t(this->r - other, this->g - other, this->b - other);
        }

        ltcolor_t operator*(ltcolor_t other) {
            return ltcolor_t(this->r * other.r, this->g * other.g, this->b * other.b);
        }

        ltcolor_t operator*(u8 other) {
            return ltcolor_t(this->r * other, this->g * other, this->b * other);
        }

        ltcolor_t operator/(ltcolor_t other) {
            return ltcolor_t(this->r / other.r, this->g / other.g, this->b / other.b);
        }


        void operator+=(ltcolor_t other) {
            this->r += other.r;
            this->g += other.g;
            this->b += other.b;
        }

        void operator+=(u8 other) {
            this->r += other;
            this->g += other;
            this->b += other;
        }

        void operator-=(ltcolor_t other) {
            this->r -= other.r;
            this->g -= other.g;
            this->b -= other.b;
        }

        void operator-=(u8 other) {
            this->r -= other;
            this->g -= other;
            this->b -= other;
        }

        void operator*=(ltcolor_t other) {
            this->r *= other.r;
            this->g *= other.g;
            this->b *= other.b;
        }

        void operator*=(u8 other) {
            this->r *= other;
            this->g *= other;
            this->b *= other;
        }

        void operator/=(ltcolor_t other) {
            this->r /= other.r;
            this->g /= other.g;
            this->b /= other.b;
        }

        void operator/=(u8 other) {
            this->r /= other;
            this->g /= other;
            this->b /= other;
        }
    } ltcolor_t;

    typedef struct ltcolora_t {
        u8 r, g, b, a;

        ltcolora_t(u8 r, u8 g, u8 b, u8 a) : r(r), g(g), b(b), a(a) {}

        operator ltcolor_t() {
            return ltcolor_t(this->r, this->g, this->b);
        }

        ltcolora_t operator=(ltcolor_t other) {
            return ltcolora_t(other.r, other.g, other.b, this->a);
        }

        ltcolora_t operator+(ltcolora_t other) {
            return ltcolora_t(this->r + other.r, this->g + other.g, this->b + other.b, this->a + other.a);
        }

        ltcolora_t operator+(u8 other) {
            return ltcolora_t(this->r + other, this->g + other, this->b + other, this->a);
        }

        ltcolora_t operator-(ltcolora_t other) {
            return ltcolora_t(this->r - other.r, this->g - other.g, this->b - other.b, this->a - other.a);
        }

        ltcolora_t operator-(u8 other) {
            return ltcolora_t(this->r - other, this->g - other, this->b - other, this->a);
        }

        ltcolora_t operator*(ltcolora_t other) {
            return ltcolora_t(this->r * other.r, this->g * other.g, this->b * other.b, this->a * other.a);
        }

        ltcolora_t operator*(u8 other) {
            return ltcolora_t(this->r * other, this->g * other, this->b * other, this->a);
        }

        ltcolora_t operator/(ltcolora_t other) {
            return ltcolora_t(this->r / other.r, this->g / other.g, this->b / other.b, this->a / other.a);
        }


        void operator+=(ltcolora_t other) {
            this->r += other.r;
            this->g += other.g;
            this->b += other.b;
            this->a += other.a;
        }

        void operator+=(u8 other) {
            this->r += other;
            this->g += other;
            this->b += other;
            this->a += other;
        }

        void operator-=(ltcolora_t other) {
            this->r -= other.r;
            this->g -= other.g;
            this->b -= other.b;
            this->a -= other.a;
        }

        void operator-=(u8 other) {
            this->r -= other;
            this->g -= other;
            this->b -= other;
            this->a -= other;
        }

        void operator*=(ltcolora_t other) {
            this->r *= other.r;
            this->g *= other.g;
            this->b *= other.b;
            this->a *= other.a;
        }

        void operator*=(u8 other) {
            this->r *= other;
            this->g *= other;
            this->b *= other;
            this->a *= other;
        }

        void operator/=(ltcolora_t other) {
            this->r /= other.r;
            this->g /= other.g;
            this->b /= other.b;
            this->a /= other.a;
        }

        void operator/=(u8 other) {
            this->r /= other;
            this->g /= other;
            this->b /= other;
            this->a /= other;
        }
    } ltcolora_t;
}
