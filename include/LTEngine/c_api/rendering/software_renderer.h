#ifndef _LTENGINE_C_API_SOFTWARE_RENDERER_H_
#define _LTENGINE_C_API_SOFTWARE_RENDERER_H_
#ifdef LTENGINE_COMPONENT_C_API

#include <LTEngine/c_api/rendering/renderer.h>
#include <LTEngine/c_api/rendering/cpu_shader.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef LTEngine_HRenderer LTEngine_HSoftwareRenderer;

typedef enum {
    NEAREST = 0,
    LINEAR
} LTEngine_SoftwareRenderer_ScalingMode;

LTEngine_HSoftwareRenderer LTENGINE_API LTEngine_SoftwareRenderer(LTEngine_u32 width, LTEngine_u32 height);
void LTEngine_SoftwareRenderer_free(LTEngine_HSoftwareRenderer renderer);

size_t LTENGINE_API LTEngine_SoftwareRenderer_getScreenData(LTEngine_HSoftwareRenderer renderer, LTEngine_HColor *color);
void LTENGINE_API LTEngine_SoftwareRenderer_setScreenOnly(LTEngine_HSoftwareRenderer renderer);
void LTENGINE_API LTEngine_SoftwareRenderer_clearScreenOnly(LTEngine_HSoftwareRenderer renderer);

void LTENGINE_API LTEngine_SoftwareRenderer_drawCamera(LTEngine_HSoftwareRenderer renderer, LTEngine_u32 id, LTEngine_HRecti rect, LTEngine_HColorA color, LTEngine_RendererFlags flags /* = 0 */);

bool LTENGINE_API LTEngine_SoftwareRenderer_process(LTEngine_HSoftwareRenderer renderer);
void LTENGINE_API LTEngine_SoftwareRenderer_processAll(LTEngine_HSoftwareRenderer renderer);
bool LTENGINE_API LTEngine_SoftwareRenderer_hasQueuedTasks(LTEngine_HSoftwareRenderer renderer);

void LTENGINE_API LTEngine_SoftwareRenderer_setScalingMode(LTEngine_HSoftwareRenderer renderer, LTEngine_SoftwareRenderer_ScalingMode mode);

void LTENGINE_API LTEngine_SoftwareRenderer_setShader(LTEngine_HSoftwareRenderer renderer, LTEngine_HCPUShader shader);
void LTENGINE_API LTEngine_SoftwareRenderer_clearShader(LTEngine_HSoftwareRenderer renderer);

#ifdef __cplusplus
}
#endif

#endif
#endif // _LTENGINE_C_API_SOFTWARE_RENDERER_H_