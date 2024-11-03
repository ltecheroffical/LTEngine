#pragma once

#include <LTEngine/common/types/inttypes.h>
#include <LTEngine/common/types/floattypes.h>


namespace LTEngine::Math {
    struct Vec2 {
        f32 x, y;

        Vec2(f32 x, f32 y) : x(x), y(y) {}

        Vec2 operator+(Vec2 b) {
            return Vec2(x + b.x, y + b.y);
        }

        Vec2 operator+(u32 b) {
            return Vec2(x + b, y + b);
        }

        Vec2 operator-(Vec2 b) {
            return Vec2(x - b.x, y - b.y);
        }

        Vec2 operator-(u32 b) {
            return Vec2(x - b, y - b);
        }

        Vec2 operator*(Vec2 b) {
            return Vec2(x * b.x, y * b.y);
        }
        
        Vec2 operator*(u32 b) {
            return Vec2(x * b, y * b);
        }

        Vec2 operator/(Vec2 b) {
            return Vec2(x / b.x, y / b.y);
        }

        Vec2 operator/(u32 b) {
            return Vec2(x / b, y / b);
        }


        void operator+=(Vec2 b) {
            x += b.x;
            y += b.y;
        }

        void operator+=(u32 b) {
            x += b;
            y += b;
        }

        void operator-=(Vec2 b) {
            x -= b.x;
            y -= b.y;
        }

        void operator-=(u32 b) {
            x -= b;
            y -= b;
        }

        void operator*=(Vec2 b) {
            x *= b.x;
            y *= b.y;
        }

        void operator*=(u32 b) {
            x *= b;
            y *= b;
        }

        void operator/=(Vec2 b) {
            x /= b.x;
            y /= b.y;
        }

        void operator/=(u32 b) {
            x /= b;
            y /= b;
        }
    };
    
    struct Vec2i {
        i32 x, y;

        Vec2i(i32 x, i32 y) : x(x), y(y) {}

        Vec2i operator+(Vec2i b) {
            return Vec2i(x + b.x, y + b.y);
        }

        Vec2i operator+(u32 b) {
            return Vec2i(x + b, y + b);
        }

        Vec2i operator-(Vec2i b) {
            return Vec2i(x - b.x, y - b.y);
        }

        Vec2i operator-(u32 b) {
            return Vec2i(x - b, y - b);
        }

        Vec2i operator*(Vec2i b) {
            return Vec2i(x * b.x, y * b.y);
        }
        
        Vec2i operator*(u32 b) {
            return Vec2i(x * b, y * b);
        }

        Vec2i operator/(Vec2i b) {
            return Vec2i(x / b.x, y / b.y);
        }

        Vec2i operator/(u32 b) {
            return Vec2i(x / b, y / b);
        }


        void operator+=(Vec2i b) {
            x += b.x;
            y += b.y;
        }

        void operator+=(u32 b) {
            x += b;
            y += b;
        }

        void operator-=(Vec2i b) {
            x -= b.x;
            y -= b.y;
        }

        void operator-=(u32 b) {
            x -= b;
            y -= b;
        }

        void operator*=(Vec2i b) {
            x *= b.x;
            y *= b.y;
        }

        void operator*=(u32 b) {
            x *= b;
            y *= b;
        }

        void operator/=(Vec2i b) {
            x /= b.x;
            y /= b.y;
        }

        void operator/=(u32 b) {
            x /= b;
            y /= b;
        }
    };

    struct Vec2u {
        u32 x, y;

        Vec2u(u32 x, u32 y) : x(x), y(y) {}

        Vec2u operator+(Vec2u b) {
            return Vec2u(x + b.x, y + b.y);
        }

        Vec2u operator+(u32 b) {
            return Vec2u(x + b, y + b);
        }

        Vec2u operator-(Vec2u b) {
            return Vec2u(x - b.x, y - b.y);
        }

        Vec2u operator-(u32 b) {
            return Vec2u(x - b, y - b);
        }

        Vec2u operator*(Vec2u b) {
            return Vec2u(x * b.x, y * b.y);
        }
        
        Vec2u operator*(u32 b) {
            return Vec2u(x * b, y * b);
        }

        Vec2u operator/(Vec2u b) {
            return Vec2u(x / b.x, y / b.y);
        }

        Vec2u operator/(u32 b) {
            return Vec2u(x / b, y / b);
        }


        void operator+=(Vec2u b) {
            x += b.x;
            y += b.y;
        }

        void operator+=(u32 b) {
            x += b;
            y += b;
        }

        void operator-=(Vec2u b) {
            x -= b.x;
            y -= b.y;
        }

        void operator-=(u32 b) {
            x -= b;
            y -= b;
        }

        void operator*=(Vec2u b) {
            x *= b.x;
            y *= b.y;
        }

        void operator*=(u32 b) {
            x *= b;
            y *= b;
        }

        void operator/=(Vec2u b) {
            x /= b.x;
            y /= b.y;
        }

        void operator/=(u32 b) {
            x /= b;
            y /= b;
        }
    };
}
