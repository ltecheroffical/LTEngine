#ifndef _LTENGINE_PLATFORM_RANDOM_SECURE_HPP_
#define _LTENGINE_PLATFORM_RANDOM_SECURE_HPP_

#include <LTEngine/random/openssl_random.hpp>
#include <LTEngine/random/unix_random_secure.hpp>


namespace LTEngine::Random {
// This class has the purpose of choosing the best for platform randomness that is still secure
class LTENGINE_API PlatformRandomSecure : public Random {
public:
    struct RandomSettings {
        size_t unix_random_buffer_size = 512;
    };

    PlatformRandomSecure(RandomSettings settings);
    ~PlatformRandomSecure() override = default;

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

    void next_bytes(void *data, size_t size) override;

private:
#if defined(__linux__) || defined(__APPLE__)
    UnixRandomSecure _random;
#else
    OpenOpenSSLRandom _random;
#endif
};
} // namespace LTEngine::Random

#endif
