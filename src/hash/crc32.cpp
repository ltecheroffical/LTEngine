#include <LTEngine/hash/crc32.hpp>


u32 LTEngine::Hash::crc32(const u8 *data, u32 size) {
    static u32 table[256];
    static bool initialized = false;
    
    if (!initialized) {
        for (u32 i = 0; i < 256; i++) {
            u32 crc = i;
            for (u32 j = 0; j < 8; j++) {
                crc = (crc >> 1) ^ (crc & 1 ? 0xedb88320 : 0);
            }
            table[i] = crc;
        }
        initialized = true;
    }
    
    u32 crc = 0xffffffff;
    for (u32 i = 0; i < size; i++) {
        crc = (crc >> 8) ^ table[(crc & 0xff) ^ data[i]];
    }
    return crc ^ 0xffffffff;
}
