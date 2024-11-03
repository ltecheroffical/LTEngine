#pragma once

#include <LTEngine/common/types/inttypes.h>
#include <LTEngine/common/types/floattypes.h>


namespace LTEngine::Random {
    class ltrandom_t {
    public:
        virtual ~ltrandom_t() = 0;

        virtual void seed(u8 seed);

        virtual u8 next_u8();
        virtual u8 next_u8(u8 min, u8 max);
        virtual u8 next_u8(u8 min);
        virtual u16 next_u16();
        virtual u16 next_u16(u16 min, u16 max);
        virtual u16 next_u16(u16 min);
        virtual u32 next_u32();
        virtual u32 next_u32(u32 min, u32 max);
        virtual u32 next_u32(u32 min);
        virtual u64 next_u64();
        virtual u64 next_u64(u64 min, u64 max);
        virtual u64 next_u64(u64 min);

        virtual i8 next_i8();
        virtual i8 next_i8(i8 min, i8 max);
        virtual i8 next_i8(i8 min);
        virtual i16 next_i16();
        virtual i16 next_i16(i16 min, i16 max);
        virtual i16 next_i16(i16 min);
        virtual i32 next_i32();
        virtual i32 next_i32(i32 min, i32 max);
        virtual i32 next_i32(i32 min);
        virtual i64 next_i64();
        virtual i64 next_i64(i64 min, i64 max);
        virtual i64 next_i64(i64 min);

        virtual f32 next_f32();
        virtual f32 next_f32(f32 min, f32 max);
        virtual f32 next_f32(f32 min);
        virtual f64 next_f64();
        virtual f64 next_f64(f64 min, f64 max);
        virtual f64 next_f64(f64 min);

        virtual void next_bytes(u8 *data, u32 length);
    };
}
