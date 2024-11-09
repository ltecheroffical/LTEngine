#pragma once

#include <vector>
#include <fstream>

#include <LTEngine/random/random.hpp>


namespace LTEngine::Random {
    class UnixRandom : public Random {
    public:
        UnixRandom(u32 bufferSize = 512);
        ~UnixRandom() override;

        u8 next_u8() override;
        u16 next_u16() override;
        u32 next_u32() override;
        u64 next_u64() override;

        i8 next_i8() override;
        i16 next_i16() override;
        i32 next_i32() override;
        i64 next_i64() override;

        f32 next_f32() override;
        f64 next_f64() override;

        void nextBytes(u8 *data, u32 length) override;

    private:
        u32 m_bufferSize;
        std::vector<u8> m_buffer;

        std::ifstream m_urandom;
    };
}
