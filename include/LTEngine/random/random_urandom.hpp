#pragma once

#include <LTEngine/random/random.hpp>


namespace LTEngine::Random {
    class URandom : public Random {
    public:
        URandom();
        ~URandom() override;

        void seed(u8 seed) override;

        u8 next_u8() override;
        u8 next_u8(u8 min, u8 max) override;
        u8 next_u8(u8 min) override;
        u16 next_u16() override;
        u16 next_u16(u16 min, u16 max) override;
        u16 next_u16(u16 min) override;
        u32 next_u32() override;
        u32 next_u32(u32 min, u32 max) override;
        u32 next_u32(u32 min) override;
        u64 next_u64() override;
        u64 next_u64(u64 min, u64 max) override;
        u64 next_u64(u64 min) override;

        i8 next_i8() override;
        i8 next_i8(i8 min, i8 max) override;
        i8 next_i8(i8 min) override;
        i16 next_i16() override;
        i16 next_i16(i16 min, i16 max) override;
        i16 next_i16(i16 min) override;
        i32 next_i32() override;
        i32 next_i32(i32 min, i32 max) override;
        i32 next_i32(i32 min) override;
        i64 next_i64() override;
        i64 next_i64(i64 min, i64 max) override;
        i64 next_i64(i64 min) override;

        f32 next_f32() override;
        f32 next_f32(f32 min, f32 max) override;
        f32 next_f32(f32 min) override;
        f64 next_f64() override;
        f64 next_f64(f64 min, f64 max) override;
        f64 next_f64(f64 min) override;

        void nextBytes(u8 *data, u32 length) override;
    };
}
