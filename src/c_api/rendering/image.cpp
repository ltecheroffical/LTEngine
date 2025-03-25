#include <LTEngine/c_api/rendering/image.h>
#include <LTEngine/rendering/image.hpp>


LTENGINE_DEFINE_DYNAMIC_ARRAY_LOGIC(LTEngine_HColor, Color);
LTENGINE_DEFINE_DYNAMIC_ARRAY_LOGIC(LTEngine_HColorA, ColorA);


LTEngine::Rendering::Color cColorToCPPColor(LTEngine_HColor color);
std::vector<LTEngine::Rendering::Color> cArrColorToCPPColor(LTEngine_DynamicArray_Color *array);

LTEngine::Rendering::ColorA cColorAToCPPColorA(LTEngine_HColorA color);
std::vector<LTEngine::Rendering::ColorA> cArrColorAToCPPColorA(LTEngine_DynamicArray_ColorA *array);


LTEngine_HImage LTEngine_Image(LTEngine_u32 width, LTEngine_u32 height) {
    return {{new LTEngine::Rendering::Image(width, height)}};
}

LTEngine_HImage LTengine_Image_data(LTEngine_u32 width, LTEngine_u32 height, LTEngine_DynamicArray_Color data) {
    return {{new LTEngine::Rendering::Image(
        cArrColorToCPPColor(&data).data(),
        width, height)}};
}

LTEngine_HImage LTEngine_Image_dataA(LTEngine_u32 width, LTEngine_u32 height, LTEngine_DynamicArray_ColorA data) {
    std::vector<LTEngine::Rendering::ColorA> dataA;
    dataA.reserve(LTEngine_DynamicArray_ColorA_size(&data));
    for (size_t i = 0; i < LTEngine_DynamicArray_ColorA_size(&data); i++) {
        LTEngine_HColorA color = LTEngine_DynamicArray_ColorA_get(&data, i);
        dataA.push_back({
            LTEngine_ColorA_r(color),
            LTEngine_ColorA_g(color),
            LTEngine_ColorA_b(color),
            LTEngine_ColorA_a(color)
        });
    }

    return {{new LTEngine::Rendering::Image(dataA.data(), width, height)}};
}


void LTEngine_Image_setSize(LTEngine_HImage handle, LTEngine_u32 width, LTEngine_u32 height) {
    ((LTEngine::Rendering::Image*)handle.handle.ptr)->setSize(width, height);
}

LTEngine_HVec2u LTEngine_Image_getSize(const LTEngine_HImage handle) {
    auto size = ((LTEngine::Rendering::Image*)handle.handle.ptr)->getSize();
    return LTEngine_Vec2u(size.x, size.y);
}


void LTEngine_Image_setPixel(LTEngine_HImage handle, const LTEngine_HColorA color, LTEngine_u32 x, LTEngine_u32 y) {
    ((LTEngine::Rendering::Image*)handle.handle.ptr)->setPixel(cColorAToCPPColorA(color), x, y);
}

LTEngine_HColorA LTEngine_Image_getPixel(const LTEngine_HImage handle, LTEngine_u32 x, LTEngine_u32 y) {
    auto color = ((LTEngine::Rendering::Image*)handle.handle.ptr)->getPixel(x, y);
    return LTEngine_ColorA(color.r, color.g, color.b, color.a);
}


void LTEngine_Image_flipH(LTEngine_HImage handle) {
    ((LTEngine::Rendering::Image*)handle.handle.ptr)->flipH();
}

void LTEngine_Image_flipV(LTEngine_HImage handle) {
    ((LTEngine::Rendering::Image*)handle.handle.ptr)->flipV();
}


void LTEngine_Image_load(LTEngine_HImage handle, const char *filename) {
    ((LTEngine::Rendering::Image*)handle.handle.ptr)->load(filename);
}

void LTEngine_Image_loadBuffer(LTEngine_HImage handle, LTEngine_u8 *buffer, size_t size) {
    ((LTEngine::Rendering::Image*)handle.handle.ptr)->load(buffer, size);
}


LTEngine_DynamicArray_ColorA LTEngine_Image_getMemBuffer(const LTEngine_HImage handle) {
    auto data = ((LTEngine::Rendering::Image*)handle.handle.ptr)->getMemBuffer();
    LTEngine_DynamicArray_ColorA cData = LTEngine_DynamicArray_ColorA_createWithCapacity(((LTEngine::Rendering::Image*)handle.handle.ptr)->getSize().x * ((LTEngine::Rendering::Image*)handle.handle.ptr)->getSize().y);
    for (size_t i = 0; i < ((LTEngine::Rendering::Image*)handle.handle.ptr)->getSize().x * ((LTEngine::Rendering::Image*)handle.handle.ptr)->getSize().y; i++) {
        LTEngine_DynamicArray_ColorA_add(&cData, LTEngine_ColorA(data[i].r, data[i].g, data[i].b, data[i].a));
    }
    return cData;
}

void LTEngine_Image_setMemBuffer(LTEngine_HImage handle, LTEngine_DynamicArray_ColorA *buffer) {
    std::memcpy(((LTEngine::Rendering::Image*)handle.handle.ptr)->getMemBuffer(), cArrColorAToCPPColorA(buffer).data(), LTEngine_DynamicArray_ColorA_size(buffer));
}


void LTEngine_Image_savePNG(const LTEngine_HImage handle, const char *filename) {
    ((LTEngine::Rendering::Image*)handle.handle.ptr)->savePNG(filename);
}

void LTEngine_Image_saveBMP(const LTEngine_HImage handle, const char *filename) {
    ((LTEngine::Rendering::Image*)handle.handle.ptr)->saveBMP(filename);
}

void LTEngine_Image_saveJPG(const LTEngine_HImage handle, const char *filename) {
    ((LTEngine::Rendering::Image*)handle.handle.ptr)->saveJPG(filename);
}

LTEngine_DynamicArray_u8 LTEngine_Image_saveBufferPNG(const LTEngine_HImage handle) {
    auto data = ((LTEngine::Rendering::Image*)handle.handle.ptr)->savePNG();
    LTEngine_DynamicArray_u8 cData = LTEngine_DynamicArray_u8_createWithCapacity(data.size());
    
    for (LTEngine::u8 arrData : data) {
        LTEngine_DynamicArray_u8_add(&cData, arrData);
    }
    return cData;
}

LTEngine_DynamicArray_u8 LTEngine_Image_saveBufferBMP(const LTEngine_HImage handle) {
    auto data = ((LTEngine::Rendering::Image*)handle.handle.ptr)->saveBMP();
    LTEngine_DynamicArray_u8 cData = LTEngine_DynamicArray_u8_createWithCapacity(data.size());
    
    for (LTEngine::u8 arrData : data) {
        LTEngine_DynamicArray_u8_add(&cData, arrData);        
    }
    return cData;
}

LTEngine_DynamicArray_u8 LTEngine_Image_saveBufferJPG(const LTEngine_HImage handle) {
    auto data = ((LTEngine::Rendering::Image*)handle.handle.ptr)->saveJPG();
    LTEngine_DynamicArray_u8 cData = LTEngine_DynamicArray_u8_createWithCapacity(data.size());
    
    for (LTEngine::u8 arrData : data) {
        LTEngine_DynamicArray_u8_add(&cData, arrData);        
    }
    return cData;
}




LTEngine::Rendering::Color cColorToCPPColor(LTEngine_HColor color) {
    return LTEngine::Rendering::Color{
        LTEngine_Color_r(color),
        LTEngine_Color_g(color),
        LTEngine_Color_b(color),
    };
}

std::vector<LTEngine::Rendering::Color> cArrColorToCPPColor(LTEngine_DynamicArray_Color *array) {
    std::vector<LTEngine::Rendering::Color> data;
    data.reserve(LTEngine_DynamicArray_Color_size(array));
    for (size_t i = 0; i < LTEngine_DynamicArray_Color_size(array); i++) {
        LTEngine_HColor color = LTEngine_DynamicArray_Color_get(array, i);
        data.push_back({
            LTEngine_Color_r(color),
            LTEngine_Color_g(color),
            LTEngine_Color_b(color),
        });
    }
    return data;
}


LTEngine::Rendering::ColorA cColorAToCPPColorA(LTEngine_HColorA color) {
    return LTEngine::Rendering::ColorA{
        LTEngine_ColorA_r(color),
        LTEngine_ColorA_g(color),
        LTEngine_ColorA_b(color),
        LTEngine_ColorA_a(color)
    };
}

std::vector<LTEngine::Rendering::ColorA> cArrColorAToCPPColorA(LTEngine_DynamicArray_ColorA *array) {
    std::vector<LTEngine::Rendering::ColorA> dataA;
    dataA.reserve(LTEngine_DynamicArray_ColorA_size(array));
    for (size_t i = 0; i < LTEngine_DynamicArray_ColorA_size(array); i++) {
        LTEngine_HColorA color = LTEngine_DynamicArray_ColorA_get(array, i);
        dataA.push_back({
            LTEngine_ColorA_r(color),
            LTEngine_ColorA_g(color),
            LTEngine_ColorA_b(color),
            LTEngine_ColorA_a(color)
        });
    }
    return dataA;
}