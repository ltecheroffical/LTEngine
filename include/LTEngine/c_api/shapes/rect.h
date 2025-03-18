#ifndef _LTENGINE_C_API_RECT_H_
#define _LTENGINE_C_API_RECT_H_

#include <LTEngine/c_api/common/ctypes.h>
#include <LTEngine/common/compiler_utils.h>

#include <LTEngine/c_api/shapes/shape.h>


typedef LTEngine_HShape LTEngine_HRect;
typedef LTEngine_HShapei LTEngine_HRecti;


#ifdef __cplusplus
extern "C" {
#endif

LTEngine_HRect LTENGINE_API LTEngine_Rect(LTEngine_f32 x, LTEngine_f32 y, LTEngine_f32 w, LTEngine_f32 h);
void LTENGINE_API LTEngine_Rect_free(LTEngine_HRect handle);

LTEngine_f32 LTENGINE_API LTEngine_Rect_w(const LTEngine_HRect handle);
LTEngine_f32 LTENGINE_API LTEngine_Rect_h(const LTEngine_HRect handle);

void LTENGINE_API LTEngine_Rect_setW(LTEngine_HRect handle, LTEngine_f32 w);
void LTENGINE_API LTEngine_Rect_setH(LTEngine_HRect handle, LTEngine_f32 h);


LTEngine_HRecti LTENGINE_API LTEngine_Recti(LTEngine_i32 x, LTEngine_i32 y, LTEngine_u32 w, LTEngine_u32 h);
void LTENGINE_API LTEngine_Recti_free(LTEngine_HRecti handle);

LTEngine_u32 LTENGINE_API LTEngine_Recti_w(const LTEngine_HRecti handle);
LTEngine_u32 LTENGINE_API LTEngine_Recti_h(const LTEngine_HRecti handle);

void LTENGINE_API LTEngine_Recti_setW(LTEngine_HRecti handle, LTEngine_u32 w);
void LTENGINE_API LTEngine_Recti_setH(LTEngine_HRecti handle, LTEngine_u32 h);

#ifdef __cplusplus
}
#endif
#endif
