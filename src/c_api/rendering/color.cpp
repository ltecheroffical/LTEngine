#include <LTEngine/c_api/rendering/color.h>

#include <LTEngine/rendering/color.hpp>


LTEngine_HColor LTEngine_Color(LTEngine_u8 r, LTEngine_u8 g, LTEngine_u8 b) {
    return {{new LTEngine::Rendering::Color(r, g, b)}};
}

LTEngine_HColor LTEngine_Color_default(LTEngine_ColorDefaults preset) {
    constexpr LTEngine_u8 lookup_table[][3] = {
        /* Black */ {0x00, 0x00, 0x00},
        /* White */ {0xFF, 0xFF, 0xFF},
        /* Red */ {0xFF, 0x00, 0x00},
        /* Green */ {0x00, 0xFF, 0x00},
        /* Blue */ {0x00, 0x00, 0xFF},
        /* Yellow */ {0xFF, 0xFF, 0x00},
        /* Cyan */ {0x00, 0xFF, 0xFF}
    };

    return {{ new LTEngine::Rendering::Color(lookup_table[preset][0], lookup_table[preset][1], lookup_table[preset][2]) }};
}

void LTEngine_Color_free(LTEngine_HColor handle) {
    delete (LTEngine::Rendering::Color*)handle.handle.ptr;
}


LTEngine_u8 LTEngine_Color_r(const LTEngine_HColor handle) {
    return ((LTEngine::Rendering::Color*)handle.handle.ptr)->r;
}

LTEngine_u8 LTEngine_Color_g(const LTEngine_HColor handle) {
    return ((LTEngine::Rendering::Color*)handle.handle.ptr)->g;
}

LTEngine_u8 LTEngine_Color_b(const LTEngine_HColor handle) { 
    return ((LTEngine::Rendering::Color*)handle.handle.ptr)->b;
}


void LTEngine_Color_setR(LTEngine_HColor handle, LTEngine_u8 r) {
    ((LTEngine::Rendering::Color*)handle.handle.ptr)->r = r;
}

void LTEngine_Color_setG(LTEngine_HColor handle, LTEngine_u8 g) {
    ((LTEngine::Rendering::Color*)handle.handle.ptr)->g = g;
}

void LTEngine_Color_setB(LTEngine_HColor handle, LTEngine_u8 b) {
    ((LTEngine::Rendering::Color*)handle.handle.ptr)->b = b;
}




LTEngine_HColorA LTEngine_ColorA(LTEngine_u8 r, LTEngine_u8 g, LTEngine_u8 b, LTEngine_u8 a) {
    return {{new LTEngine::Rendering::ColorA(r, g, b, a)}};
}

LTEngine_HColorA LTEngine_ColorA_default(LTEngine_ColorDefaults preset) {
    constexpr LTEngine_u8 lookup_table[][4] = {
        /* Clear */ {0x00, 0x00, 0x00, 0x00},
        /* Black */ {0x00, 0x00, 0x00, 0xFF},
        /* White */ {0xFF, 0xFF, 0xFF, 0xFF},
        /* Red */ {0xFF, 0x00, 0x00, 0xFF},
        /* Green */ {0x00, 0xFF, 0x00, 0xFF},
        /* Blue */ {0x00, 0x00, 0xFF, 0xFF},
        /* Yellow */ {0xFF, 0xFF, 0x00, 0xFF},
        /* Cyan */ {0x00, 0xFF, 0xFF, 0xFF}
    };

    return {{ new LTEngine::Rendering::ColorA(lookup_table[preset][0], lookup_table[preset][1], lookup_table[preset][2], lookup_table[preset][3]) }};
}

void LTEngine_ColorA_free(LTEngine_HColorA handle) {
    delete (LTEngine::Rendering::ColorA*)handle.handle.ptr;
}


LTEngine_u8 LTEngine_ColorA_r(const LTEngine_HColorA handle) {
    return ((LTEngine::Rendering::ColorA*)handle.handle.ptr)->r;
}

LTEngine_u8 LTEngine_ColorA_g(const LTEngine_HColorA handle) {
    return ((LTEngine::Rendering::ColorA*)handle.handle.ptr)->g;
}

LTEngine_u8 LTEngine_ColorA_b(const LTEngine_HColorA handle) { 
    return ((LTEngine::Rendering::ColorA*)handle.handle.ptr)->b;
}

LTEngine_u8 LTEngine_ColorA_a(const LTEngine_HColorA handle) { 
    return ((LTEngine::Rendering::ColorA*)handle.handle.ptr)->a;
}


void LTEngine_ColorA_setR(LTEngine_HColorA handle, LTEngine_u8 r) {
    ((LTEngine::Rendering::ColorA*)handle.handle.ptr)->r = r;
}

void LTEngine_ColorA_setG(LTEngine_HColorA handle, LTEngine_u8 g) {
    ((LTEngine::Rendering::ColorA*)handle.handle.ptr)->g = g;
}

void LTEngine_ColorA_setB(LTEngine_HColorA handle, LTEngine_u8 b) {
    ((LTEngine::Rendering::ColorA*)handle.handle.ptr)->b = b;
}

void LTEngine_ColorA_setA(LTEngine_HColorA handle, LTEngine_u8 a) {
    ((LTEngine::Rendering::ColorA*)handle.handle.ptr)->a = a;
}