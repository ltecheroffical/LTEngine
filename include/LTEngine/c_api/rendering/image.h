#ifndef _LTENGINE_C_API_IMAGE_H_I
#ifdef LTENGINE_COMPONENT_C_API
#define _LTENGINE_C_API_IMAGE_H_

#include <stddef.h>

#include <LTEngine/c_api/common/ctypes.h>
#include <LTEngine/common/compiler_utils.h>

#include <LTEngine/c_api/math/vec2.h>
#include <LTEngine/c_api/rendering/color.h>
#include <LTEngine/c_api/list/dynamic_array.h>

#ifdef __cplusplus
extern "C" {
#endif

LTENGINE_DEFINE_DYNAMIC_ARRAY(LTEngine_HColor, Color);
LTENGINE_DEFINE_DYNAMIC_ARRAY(LTEngine_HColorA, ColorA);

typedef struct {
    LTEngine_HANDLE handle;
} LTEngine_HImage;

LTEngine_HImage LTENGINE_API LTEngine_Image(LTEngine_u32 width, LTEngine_u32 height);
LTEngine_HImage LTENGINE_API LTEngine_Image_data(LTEngine_u32 width, LTEngine_u32 height, LTEngine_DynamicArray_Color data);
LTEngine_HImage LTENGINE_API LTEngine_Image_dataA(LTEngine_u32 width, LTEngine_u32 height, LTEngine_DynamicArray_ColorA data);

void LTENGINE_API LTEngine_Image_setSize(LTEngine_HImage handle, LTEngine_u32 width, LTEngine_u32 height);
LTEngine_HVec2u LTENGINE_API LTEngine_Image_getSize(const LTEngine_HImage handle);

void LTENGINE_API LTEngine_Image_setPixel(LTEngine_HImage handle, const LTEngine_HColorA color, LTEngine_u32 x, LTEngine_u32 y);
LTEngine_HColorA LTENGINE_API LTEngine_Image_getPixel(const LTEngine_HImage handle, LTEngine_u32 x, LTEngine_u32 y);

void LTENGINE_API LTEngine_Image_flipH(LTEngine_HImage handle);
void LTENGINE_API LTEngine_Image_flipV(LTEngine_HImage handle);

void LTENGINE_API LTEngine_Image_load(LTEngine_HImage handle, const char *filename);
void LTENGINE_API LTEngine_Image_loadBuffer(LTEngine_HImage handle, LTEngine_u8 *buffer, size_t size);

LTEngine_DynamicArray_ColorA LTENGINE_API LTEngine_Image_getMemBuffer(const LTEngine_HImage handle);
void LTENGINE_API LTEngine_Image_setMemBuffer(LTEngine_HImage handle, LTEngine_DynamicArray_ColorA *buffer);

void LTENGINE_API LTEngine_Image_savePNG(const LTEngine_HImage handle, const char *filename);
void LTENGINE_API LTEngine_Image_saveBMP(const LTEngine_HImage handle, const char *filename);
void LTENGINE_API LTEngine_Image_saveJPG(const LTEngine_HImage handle, const char *filename);
LTEngine_DynamicArray_u8 LTENGINE_API LTEngine_Image_saveBufferPNG(const LTEngine_HImage handle);
LTEngine_DynamicArray_u8 LTENGINE_API LTEngine_Image_saveBufferBMP(const LTEngine_HImage handle);
LTEngine_DynamicArray_u8 LTENGINE_API LTEngine_Image_saveBufferJPG(const LTEngine_HImage handle);

#ifdef __cplusplus
}
#endif
#endif
#endif