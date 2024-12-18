#ifndef _LTENGINE_C_API_RENDERER_H_
#define _LTENGINE_C_API_RENDERER_H_

#include <LTEngine/c_api/math/vec2.h>

#include <LTEngine/c_api/rendering/color.h>

#include <LTEngine/common/compiler_utils.h>

#include <LTEngine/common/types/floattypes.h>
#include <LTEngine/common/types/inttypes.h>


typedef struct LTENGINE_API {
	void *_renderer;

} LTEngine_Renderer;

#ifdef __cplusplus
extern "C" {
#endif


void LTENGINE_API LTEngine_SetRendererZOrder(LTEngine_Renderer *renderer, LTEngine_u16 z_order);

void LTENGINE_API LTEngine_SetRendererRotationOffset(LTEngine_Renderer *renderer, LTEngine_f32 offset);
void LTENGINE_API LTEngine_SetRendererScaleFactor(LTEngine_Renderer *renderer, LTEngine_f32 offset);
void LTENGINE_API LTEngine_SetRendererPositionOffset(LTEngine_Renderer *renderer, LTEngine_f32 offset);

void LTENGINE_API LTEngine_ResetRendererTransform(LTEngine_Renderer *renderer);

void LTENGINE_API LTEngine_SetRendererIrisMode(LTEngine_Renderer *renderer);
void LTENGINE_API LTEngine_ClearRendererIrisMode(LTEngine_Renderer *renderer);

LTEngine_u32 LTENGINE_API LTEngine_CreateRendererCamera(LTEngine_Renderer *renderer);
void LTENGINE_API LTEngine_DeleteRendererCamera(LTEngine_Renderer *renderer, LTEngine_u32 id);
void LTENGINE_API LTEngine_SetRendererCameraPosition(LTEngine_Renderer *renderer, LTEngine_u32 id, LTEngine_Vec2 *position);
void LTENGINE_API LTEngine_SetRendererCameraRotation(LTEngine_Renderer *renderer, LTEngine_u32 id, LTEngine_f32 rotation);
void LTENGINE_API LTEngine_SetRendererCameraZoom(LTEngine_Renderer *renderer, LTEngine_u32 id, LTEngine_Vec2 *zoom);
void LTENGINE_API LTEngine_SetRendererCameraInclude(LTEngine_Renderer *renderer, LTEngine_u32 id);
void LTENGINE_API LTEngine_SetRendererCameraExclude(LTEngine_Renderer *renderer, LTEngine_u32 id);
void LTENGINE_API LTEngine_SetRendererCurrentCamera(LTEngine_Renderer *renderer, LTEngine_u32 id);
void LTENGINE_API LTEngine_ClearRendererCurrentCamera(LTEngine_Renderer *renderer);
LTEngine_Vec2 LTENGINE_API LTEngine_GetRendererCameraPosition(LTEngine_Renderer *renderer, LTEngine_u32 id);
LTEngine_Vec2 LTENGINE_API LTEngine_GetRendererCameraZoom(LTEngine_Renderer *renderer, LTEngine_u32 id);
LTEngine_f32 LTENGINE_API LTEngine_GetRendererCameraRotation(LTEngine_Renderer *renderer, LTEngine_u32 id);

void LTENGINE_API LTEngine_RendererClear(LTEngine_Renderer *renderer, LTEngine_color_t *color);
void LTENGINE_API LTEngine_RendererClearA(LTEngine_Renderer *renderer, LTEngine_colora_t *color);

void LTENGINE_API LTEngine_RendererSetPixel(LTEngine_Renderer *renderer, LTEngine_Vec2i *position, LTEngine_color_t *color);
void LTENGINE_API LTEngine_RendererSetPixelA(LTEngine_Renderer *renderer, LTEngine_Vec2i *position, LTEngine_colora_t *color);
LTEngine_color_t LTENGINE_API LTEngine_RendererGetPixel(LTEngine_Renderer *renderer, LTEngine_Vec2i *position);


#ifdef __cplusplus
}
#endif
#endif
