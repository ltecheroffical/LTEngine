#pragma once

#include <LTEngine/common/types/inttypes.h>


namespace LTEngine::Rendering {
    struct Color {
        u8 r, g, b;

        Color(u8 r, u8 g, u8 b) : r(r), g(g), b(b) {}

        Color operator+(Color other) {
            return Color(this->r + other.r, this->g + other.g, this->b + other.b);
        }

        Color operator+(u8 other) {
            return Color(this->r + other, this->g + other, this->b + other);
        }

        Color operator-(Color other) {
            return Color(this->r - other.r, this->g - other.g, this->b - other.b);
        }

        Color operator-(u8 other) {
            return Color(this->r - other, this->g - other, this->b - other);
        }

        Color operator*(Color other) {
            return Color(this->r * other.r, this->g * other.g, this->b * other.b);
        }

        Color operator*(u8 other) {
            return Color(this->r * other, this->g * other, this->b * other);
        }

        Color operator/(Color other) {
            return Color(this->r / other.r, this->g / other.g, this->b / other.b);
        }


        void operator+=(Color other) {
            this->r += other.r;
            this->g += other.g;
            this->b += other.b;
        }

        void operator+=(u8 other) {
            this->r += other;
            this->g += other;
            this->b += other;
        }

        void operator-=(Color other) {
            this->r -= other.r;
            this->g -= other.g;
            this->b -= other.b;
        }

        void operator-=(u8 other) {
            this->r -= other;
            this->g -= other;
            this->b -= other;
        }

        void operator*=(Color other) {
            this->r *= other.r;
            this->g *= other.g;
            this->b *= other.b;
        }

        void operator*=(u8 other) {
            this->r *= other;
            this->g *= other;
            this->b *= other;
        }

        void operator/=(Color other) {
            this->r /= other.r;
            this->g /= other.g;
            this->b /= other.b;
        }

        void operator/=(u8 other) {
            this->r /= other;
            this->g /= other;
            this->b /= other;
        }
    };

    struct ColorA {
        u8 r, g, b, a;

        ColorA(u8 r, u8 g, u8 b, u8 a) : r(r), g(g), b(b), a(a) {}

        operator Color() {
            return Color(this->r, this->g, this->b);
        }

        ColorA operator=(ColorA other) {
            return ColorA(other.r, other.g, other.b, this->a);
        }

        ColorA operator+(ColorA other) {
            return ColorA(this->r + other.r, this->g + other.g, this->b + other.b, this->a + other.a);
        }

        ColorA operator+(u8 other) {
            return ColorA(this->r + other, this->g + other, this->b + other, this->a);
        }

        ColorA operator-(ColorA other) {
            return ColorA(this->r - other.r, this->g - other.g, this->b - other.b, this->a - other.a);
        }

        ColorA operator-(u8 other) {
            return ColorA(this->r - other, this->g - other, this->b - other, this->a);
        }

        ColorA operator*(ColorA other) {
            return ColorA(this->r * other.r, this->g * other.g, this->b * other.b, this->a * other.a);
        }

        ColorA operator*(u8 other) {
            return ColorA(this->r * other, this->g * other, this->b * other, this->a);
        }

        ColorA operator/(ColorA other) {
            return ColorA(this->r / other.r, this->g / other.g, this->b / other.b, this->a / other.a);
        }


        void operator+=(ColorA other) {
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

        void operator-=(ColorA other) {
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

        void operator*=(ColorA other) {
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

        void operator/=(ColorA other) {
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
    };
}
