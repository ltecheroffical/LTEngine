#pragma once

#include <LTEngine/random/random.hpp>


namespace LTEngine::Random {
    class RandomUnsecure : public Random {
    public:
        RandomUnsecure() = default;
        virtual ~RandomUnsecure() = default;

        virtual u8 next_u8() override;
        virtual u16 next_u16() override;
        virtual u32 next_u32() override;
        virtual u64 next_u64() override;

        virtual i8 next_i8() override;
        virtual i16 next_i16() override;
        virtual i32 next_i32() override;
        virtual i64 next_i64() override;

        virtual f32 next_f32() override;
        virtual f64 next_f64() override;

    private:
        u16 m_index;
    };
}
