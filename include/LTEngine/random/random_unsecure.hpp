#pragma once

#include <LTEngine/random/random.hpp>


namespace LTEngine::Random {
    class RandomUnsecure : public Random {
    public:
        RandomUnsecure() = default;
        virtual ~RandomUnsecure() = default;

        virtual void seed(u8 seed) override;

        virtual u8 next_u8() override;
        virtual u8 next_u8(u8 min, u8 max) override;
        virtual u8 next_u8(u8 min) override;
        virtual u16 next_u16() override;
        virtual u16 next_u16(u16 min, u16 max) override;
        virtual u16 next_u16(u16 min) override;
        virtual u32 next_u32() override;
        virtual u32 next_u32(u32 min, u32 max) override;
        virtual u32 next_u32(u32 min) override;
        virtual u64 next_u64() override;
        virtual u64 next_u64(u64 min, u64 max) override;
        virtual u64 next_u64(u64 min) override;

        virtual i8 next_i8() override;
        virtual i8 next_i8(i8 min, i8 max) override;
        virtual i8 next_i8(i8 min) override;

        virtual i16 next_i16() override;
        virtual i16 next_i16(i16 min, i16 max) override;
        virtual i16 next_i16(i16 min) override;

        virtual i32 next_i32() override;
        virtual i32 next_i32(i32 min, i32 max) override;
        virtual i32 next_i32(i32 min) override;

        virtual i64 next_i64() override;
        virtual i64 next_i64(i64 min, i64 max) override;
        virtual i64 next_i64(i64 min) override;

        virtual f32 next_f32() override;
        virtual f32 next_f32(f32 min, f32 max) override;
        virtual f32 next_f32(f32 min) override;
        virtual f64 next_f64() override;
        virtual f64 next_f64(f64 min, f64 max) override;
        virtual f64 next_f64(f64 min) override;

    private:
        u16 m_index;
    };
}
