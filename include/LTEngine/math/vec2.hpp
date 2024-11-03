#pragma once

#include <LTEngine/common/types/inttypes.h>
#include <LTEngine/common/types/floattypes.h>


namespace LTEngine::Math {
    typedef struct ltvec2_t {
        f32 x, y;

        ltvec2_t(f32 x, f32 y) : x(x), y(y) {}

        ltvec2_t operator+(ltvec2_t b) {
            return ltvec2_t(x + b.x, y + b.y);
        }

        ltvec2_t operator+(u32 b) {
            return ltvec2_t(x + b, y + b);
        }

        ltvec2_t operator-(ltvec2_t b) {
            return ltvec2_t(x - b.x, y - b.y);
        }

        ltvec2_t operator-(u32 b) {
            return ltvec2_t(x - b, y - b);
        }

        ltvec2_t operator*(ltvec2_t b) {
            return ltvec2_t(x * b.x, y * b.y);
        }
        
        ltvec2_t operator*(u32 b) {
            return ltvec2_t(x * b, y * b);
        }

        ltvec2_t operator/(ltvec2_t b) {
            return ltvec2_t(x / b.x, y / b.y);
        }

        ltvec2_t operator/(u32 b) {
            return ltvec2_t(x / b, y / b);
        }


        void operator+=(ltvec2_t b) {
            x += b.x;
            y += b.y;
        }

        void operator+=(u32 b) {
            x += b;
            y += b;
        }

        void operator-=(ltvec2_t b) {
            x -= b.x;
            y -= b.y;
        }

        void operator-=(u32 b) {
            x -= b;
            y -= b;
        }

        void operator*=(ltvec2_t b) {
            x *= b.x;
            y *= b.y;
        }

        void operator*=(u32 b) {
            x *= b;
            y *= b;
        }

        void operator/=(ltvec2_t b) {
            x /= b.x;
            y /= b.y;
        }

        void operator/=(u32 b) {
            x /= b;
            y /= b;
        }
    } ltvec2_t;
    
    typedef struct ltvec2i_t {
        i32 x, y;

        ltvec2i_t(i32 x, i32 y) : x(x), y(y) {}

        ltvec2i_t operator+(ltvec2i_t b) {
            return ltvec2i_t(x + b.x, y + b.y);
        }

        ltvec2i_t operator+(u32 b) {
            return ltvec2i_t(x + b, y + b);
        }

        ltvec2i_t operator-(ltvec2i_t b) {
            return ltvec2i_t(x - b.x, y - b.y);
        }

        ltvec2i_t operator-(u32 b) {
            return ltvec2i_t(x - b, y - b);
        }

        ltvec2i_t operator*(ltvec2i_t b) {
            return ltvec2i_t(x * b.x, y * b.y);
        }
        
        ltvec2i_t operator*(u32 b) {
            return ltvec2i_t(x * b, y * b);
        }

        ltvec2i_t operator/(ltvec2i_t b) {
            return ltvec2i_t(x / b.x, y / b.y);
        }

        ltvec2i_t operator/(u32 b) {
            return ltvec2i_t(x / b, y / b);
        }


        void operator+=(ltvec2i_t b) {
            x += b.x;
            y += b.y;
        }

        void operator+=(u32 b) {
            x += b;
            y += b;
        }

        void operator-=(ltvec2i_t b) {
            x -= b.x;
            y -= b.y;
        }

        void operator-=(u32 b) {
            x -= b;
            y -= b;
        }

        void operator*=(ltvec2i_t b) {
            x *= b.x;
            y *= b.y;
        }

        void operator*=(u32 b) {
            x *= b;
            y *= b;
        }

        void operator/=(ltvec2i_t b) {
            x /= b.x;
            y /= b.y;
        }

        void operator/=(u32 b) {
            x /= b;
            y /= b;
        }
    } ltvec2i_i;

    typedef struct ltvec2u_t {
        u32 x, y;

        ltvec2u_t(u32 x, u32 y) : x(x), y(y) {}

        ltvec2u_t operator+(ltvec2u_t b) {
            return ltvec2u_t(x + b.x, y + b.y);
        }

        ltvec2u_t operator+(u32 b) {
            return ltvec2u_t(x + b, y + b);
        }

        ltvec2u_t operator-(ltvec2u_t b) {
            return ltvec2u_t(x - b.x, y - b.y);
        }

        ltvec2u_t operator-(u32 b) {
            return ltvec2u_t(x - b, y - b);
        }

        ltvec2u_t operator*(ltvec2u_t b) {
            return ltvec2u_t(x * b.x, y * b.y);
        }
        
        ltvec2u_t operator*(u32 b) {
            return ltvec2u_t(x * b, y * b);
        }

        ltvec2u_t operator/(ltvec2u_t b) {
            return ltvec2u_t(x / b.x, y / b.y);
        }

        ltvec2u_t operator/(u32 b) {
            return ltvec2u_t(x / b, y / b);
        }


        void operator+=(ltvec2u_t b) {
            x += b.x;
            y += b.y;
        }

        void operator+=(u32 b) {
            x += b;
            y += b;
        }

        void operator-=(ltvec2u_t b) {
            x -= b.x;
            y -= b.y;
        }

        void operator-=(u32 b) {
            x -= b;
            y -= b;
        }

        void operator*=(ltvec2u_t b) {
            x *= b.x;
            y *= b.y;
        }

        void operator*=(u32 b) {
            x *= b;
            y *= b;
        }

        void operator/=(ltvec2u_t b) {
            x /= b.x;
            y /= b.y;
        }

        void operator/=(u32 b) {
            x /= b;
            y /= b;
        }
    } ltvec2u_t;
}
