#ifndef _LTENGINE_C_API_RECT_H_
#define _LTENGINE_C_API_RECT_H_

#include <LTEngine/c_api/common/ctypes.h>
#include <LTEngine/common/compiler_utils.h>


typedef LTEngine_HANDLE LTEngine_HRect;
typedef LTEngine_HANDLE LTEngine_HRecti;


#ifdef __cplusplus
extern "C" {
#endif

LTEngine_HRect LTENGINE_API LTEngine_Rect_init(LTEngine_f32 x, LTEngine_f32 y, LTEngine_f32 w, LTEngine_f32 h);
void LTENGINE_API LTEngine_Rect_free(LTEngine_HRect handle);

LTEngine_f32 LTENGINE_API LTEngine_Rect_x(const LTEngine_HRect handle);
LTEngine_f32 LTENGINE_API LTEngine_Rect_y(const LTEngine_HRect handle);
LTEngine_f32 LTENGINE_API LTEngine_Rect_w(const LTEngine_HRect handle);
LTEngine_f32 LTENGINE_API LTEngine_Rect_h(const LTEngine_HRect handle);

void LTENGINE_API LTEngine_Rect_setX(LTEngine_HRect handle, LTEngine_f32 x);
void LTENGINE_API LTEngine_Rect_setY(LTEngine_HRect handle, LTEngine_f32 y);
void LTENGINE_API LTEngine_Rect_setW(LTEngine_HRect handle, LTEngine_f32 w);
void LTENGINE_API LTEngine_Rect_setH(LTEngine_HRect handle, LTEngine_f32 h);


LTEngine_HRecti LTENGINE_API LTEngine_Recti_init(LTEngine_i32 x, LTEngine_i32 y, LTEngine_i32 w, LTEngine_i32 h);
void LTENGINE_API LTEngine_Recti_free(LTEngine_HRecti handle);

LTEngine_i32 LTENGINE_API LTEngine_Recti_x(const LTEngine_HRecti handle);
LTEngine_i32 LTENGINE_API LTEngine_Recti_y(const LTEngine_HRecti handle);
LTEngine_i32 LTENGINE_API LTEngine_Recti_w(const LTEngine_HRecti handle);
LTEngine_i32 LTENGINE_API LTEngine_Recti_h(const LTEngine_HRecti handle);

void LTENGINE_API LTEngine_Recti_setX(LTEngine_HRecti handle, LTEngine_i32 x);
void LTENGINE_API LTEngine_Recti_setY(LTEngine_HRecti handle, LTEngine_i32 y);
void LTENGINE_API LTEngine_Recti_setW(LTEngine_HRecti handle, LTEngine_i32 w);
void LTENGINE_API LTEngine_Recti_setH(LTEngine_HRecti handle, LTEngine_i32 h);

#ifdef __cplusplus
}
#endif
#endif
