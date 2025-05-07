#ifndef _LTENGINE_C_API_CPU_SHADER_H_
#define _LTENGINE_C_API_CPU_SHADER_H_
#ifdef LTENGINE_COMPONENT_C_API

#include <LTEngine/c_api/math/vec2.h>
#include <LTEngine/c_api/rendering/color.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    LTEngine_HANDLE handle;
} LTEngine_HCPUShader;

typedef struct {
    LTEngine_HVec2i position;
    LTEngine_HColorA color;

    const LTEngine_HColor *screen;
    const LTEngine_HVec2u screenSize;

    const LTEngine_HColorA *texture;
    const LTEngine_HVec2u textureSize;
    const LTEngine_HVec2u texturePos;

    const LTEngine_f32 time;
} LTEngine_CPUShaderIO;


LTEngine_HCPUShader LTENGINE_API LTEngine_CustomCPUShader(void (*fragment)(LTEngine_CPUShaderIO *io));
void LTENGINE_API LTEngine_CustomCPUShader_free(LTEngine_HCPUShader shader);

void LTEngine_CPUShader_fragment(LTEngine_HCPUShader shader, LTEngine_CPUShaderIO *io);

#ifdef __cplusplus
}
#endif
#endif
#endif // _LTENGINE_C_API_CPU_SHADER_H_