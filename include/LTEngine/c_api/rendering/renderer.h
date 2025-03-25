#ifndef _LTENGINE_C_API_RENDERER_H_
#ifdef LTENGINE_COMPONENT_C_API
#define _LTENGINE_C_API_RENDERER_H_

#include <LTEngine/common/types/inttypes.h>
#include <LTEngine/c_api/common/ctypes.h>

#include <LTEngine/c_api/rendering/image.h>
#include <LTEngine/c_api/rendering/color.h>
#include <LTEngine/c_api/shapes/rect.h>
#include <LTEngine/c_api/shapes/circle.h>
#include <LTEngine/c_api/shapes/polygon.h>
#include <LTEngine/c_api/math/vec2.h>

#ifdef __cplusplus
extern "C" {
#endif
    
typedef struct {
    LTEngine_HANDLE handle;
} LTEngine_HRenderer;

typedef LTEngine_u16 LTEngine_RendererFlags;

extern const LTEngine_RendererFlags LTEngine_Renderer_FLAG_FLIP_V;
extern const LTEngine_RendererFlags LTEngine_Renderer_FLAG_FLIP_H;


typedef struct LTENGINE_API {
    void *(*init)(LTEngine_HRenderer handle);
    void (*deinit)(LTEngine_HRenderer handle, void *ctx);

    void (*clear)(LTEngine_HRenderer handle, void *ctx, const LTEngine_HColor color);
    void (*clearA)(LTEngine_HRenderer handle, void *ctx, const LTEngine_HColorA color);

    void (*setPixel)(LTEngine_HRenderer handle, void *ctx, const LTEngine_HVec2i position, const LTEngine_HColor color);
    void (*setPixelA)(LTEngine_HRenderer handle, void *ctx, const LTEngine_HVec2i position, const LTEngine_HColorA color);
    LTEngine_HColor (*getPixel)(LTEngine_HRenderer handle, void *ctx, const LTEngine_HVec2i position);

    void (*drawRect)(LTEngine_HRenderer handle, void *ctx, const LTEngine_HRect rect, const LTEngine_HColorA color, LTEngine_RendererFlags flags);
    void (*drawCircle)(LTEngine_HRenderer handle, void *ctx, const LTEngine_HCircle circle, const LTEngine_HColorA color, LTEngine_RendererFlags flags);

    void (*drawLine)(LTEngine_HRenderer handle, void *ctx, const LTEngine_HVec2 a, const LTEngine_HVec2 b, LTEngine_u16 thickness, const LTEngine_HColorA color, LTEngine_RendererFlags flags);
    void (*drawPoints)(LTEngine_HRenderer handle, void *ctx, const LTEngine_HPolygon polygon, const LTEngine_HColorA color, LTEngine_RendererFlags flags);

    void (*drawImage)(LTEngine_HRenderer handle, void *ctx, const LTEngine_HImage image, const LTEngine_HVec2 position, LTEngine_f32 rotation, const LTEngine_HRecti region, const LTEngine_HColorA color, LTEngine_RendererFlags flags);

    void (*cameraCreated)(LTEngine_HRenderer handle, void *ctx, LTEngine_u32 id);
    void (*cameraDestroyed)(LTEngine_HRenderer handle, void *ctx, LTEngine_u32 id);
    void (*cameraSelected)(LTEngine_HRenderer handle, void *ctx, LTEngine_u32 id);
    void (*cameraDeselected)(LTEngine_HRenderer handle, void *ctx);
} LTEngine_CustomRendererFuncs;

LTEngine_HRenderer LTENGINE_API LTEngine_CustomRenderer(LTEngine_CustomRendererFuncs funcs);
void LTENGINE_API LTEngine_CustomRenderer_free(LTEngine_HRenderer handle);

void LTENGINE_API LTEngine_Renderer_setScale(LTEngine_HRenderer handle, const LTEngine_HVec2 scale);

void LTENGINE_API LTEngine_Renderer_setRotationOffset(LTEngine_HRenderer handle, LTEngine_f32 offset);
void LTENGINE_API LTEngine_Renderer_setScaleFactor(LTEngine_HRenderer handle, const LTEngine_HVec2 scale);
void LTENGINE_API LTEngine_Renderer_setPositionOffset(LTEngine_HRenderer handle, const LTEngine_HVec2 offset);

void LTENGINE_API LTEngine_Renderer_resetTransform(LTEngine_HRenderer handle);

void LTENGINE_API LTEngine_Renderer_setIrisMode(LTEngine_HRenderer handle);
void LTENGINE_API LTEngine_Renderer_clearIrisMode(LTEngine_HRenderer handle);

LTEngine_u32 LTENGINE_API LTEngine_Renderer_createCamera(LTEngine_HRenderer handle, const LTEngine_HVec2 position, const LTEngine_HVec2 zoom);
void LTENGINE_API LTEngine_Renderer_deleteCamera(LTEngine_HRenderer handle, LTEngine_u32 id);
void LTENGINE_API LTEngine_Renderer_setCameraPosition(LTEngine_HRenderer handle, LTEngine_u32 id, const LTEngine_HVec2 position);
void LTENGINE_API LTEngine_Renderer_setCameraRotation(LTEngine_HRenderer handle, LTEngine_u32 id, LTEngine_f32 rotation);
void LTENGINE_API LTEngine_Renderer_setCameraZoom(LTEngine_HRenderer handle, LTEngine_u32 id, const LTEngine_HVec2 zoom);
void LTENGINE_API LTEngine_Renderer_setCameraInclude(LTEngine_HRenderer handle, LTEngine_u32 id);
void LTENGINE_API LTEngine_Renderer_setCameraExclude(LTEngine_HRenderer handle, LTEngine_u32 id);
void LTENGINE_API LTEngine_Renderer_setCurrentCamera(LTEngine_HRenderer handle, LTEngine_u32 id);
void LTENGINE_API LTEngine_Renderer_clearCameraCamera(LTEngine_HRenderer handle);
LTEngine_HVec2 LTENGINE_API LTEngine_Renderer_getCameraPosition(const LTEngine_HRenderer handle, LTEngine_u32 id);
LTEngine_HVec2 LTENGINE_API LTEngine_Renderer_getCameraZoom(const LTEngine_HRenderer handle, LTEngine_u32 id);
LTEngine_f32 LTENGINE_API LTEngine_Renderer_getCameraRotation(const LTEngine_HRenderer handle, LTEngine_u32 id);
bool LTENGINE_API LTEngine_Renderer_isCameraIncluded(const LTEngine_HRenderer handle, LTEngine_u32 id);

void LTENGINE_API LTEngine_Renderer_clear(LTEngine_HRenderer handle, const LTEngine_HColor color);
void LTENGINE_API LTEngine_Renderer_clearA(LTEngine_HRenderer handle, const LTEngine_HColorA color);

void LTENGINE_API LTEngine_Renderer_setPixel(LTEngine_HRenderer handle, const LTEngine_HVec2i position, const LTEngine_HColor color);
void LTENGINE_API LTEngine_Renderer_setPixelA(LTEngine_HRenderer handle, const LTEngine_HVec2i position, const LTEngine_HColorA color);
LTEngine_HColor LTEngine_Renderer_getPixel(const LTEngine_HRenderer handle, const LTEngine_HVec2i position);

void LTENGINE_API LTEngine_Renderer_drawRect(LTEngine_HRenderer handle, const LTEngine_HRect rect, const LTEngine_HColorA color, LTEngine_RendererFlags flags);
void LTENGINE_API LTEngine_Renderer_drawCircle(LTEngine_HRenderer handle, const LTEngine_HCircle circle, const LTEngine_HColorA color, LTEngine_RendererFlags flags);

void LTENGINE_API LTEngine_Renderer_drawLine(LTEngine_HRenderer handle, const LTEngine_HVec2 a, const LTEngine_HVec2 b, LTEngine_u16 thickness, const LTEngine_HColorA color, LTEngine_RendererFlags flags);
void LTENGINE_API LTEngine_Renderer_drawPoints(LTEngine_HRenderer handle, const LTEngine_HPolygon polygon, const LTEngine_HColorA color, LTEngine_RendererFlags flags);

void LTENGINE_API LTEngine_Renderer_drawImage(LTEngine_HRenderer handle, const LTEngine_HImage image, const LTEngine_HVec2 position, LTEngine_f32 rotation, const LTEngine_HRecti region, const LTEngine_HColorA color, LTEngine_RendererFlags flags);

LTEngine_HVec2 LTENGINE_API LTEngine_Renderer_worldToScreenPosition(const LTEngine_HRenderer handle, const LTEngine_HVec2 position);
LTEngine_HVec2i LTENGINE_API LTEngine_Renderer_worldToScreenPositioni(const LTEngine_HRenderer handle, const LTEngine_HVec2 position);
LTEngine_f32 LTENGINE_API LTEngine_Renderer_worldToScreenRotation(const LTEngine_HRenderer handle, LTEngine_f32 rotation);

LTEngine_HVec2 LTENGINE_API LTEngine_Renderer_screenToWorldPosition(const LTEngine_HRenderer handle, const LTEngine_HVec2 position);
LTEngine_HVec2i LTENGINE_API LTEngine_Renderer_screenToWorldPositioni(const LTEngine_HRenderer handle, const LTEngine_HVec2 position);
LTEngine_f32 LTENGINE_API LTEngine_Renderer_screenToWorldRotation(const LTEngine_HRenderer handle, LTEngine_f32 rotation);

LTEngine_HVec2 LTENGINE_API LTEngine_Renderer_getWorldScale(const LTEngine_HRenderer handle);

LTEngine_u16 LTENGINE_API LTEngine_Renderer_getZOrder(const LTEngine_HRenderer handle);
bool LTENGINE_API LTEngine_Renderer_isIrisMode(const LTEngine_HRenderer handle);

LTEngine_u32 LTENGINE_API LTEngine_Renderer_getCurrentCamera(const LTEngine_HRenderer handle);
bool LTENGINE_API LTEngine_Renderer_isCameraActive(const LTEngine_HRenderer handle);

#ifdef __cplusplus
}
#endif
#endif
#endif
