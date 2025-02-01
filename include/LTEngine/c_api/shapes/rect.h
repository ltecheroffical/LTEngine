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

void LTENGINE_API LTEngine_Rect_set_x(LTEngine_HRect handle, LTEngine_f32 x);
void LTENGINE_API LTEngine_Rect_set_y(LTEngine_HRect handle, LTEngine_f32 y);
void LTENGINE_API LTEngine_Rect_set_w(LTEngine_HRect handle, LTEngine_f32 w);
void LTENGINE_API LTEngine_Rect_set_h(LTEngine_HRect handle, LTEngine_f32 h);


LTEngine_HRecti LTENGINE_API LTEngine_Recti_init(LTEngine_i32 x, LTEngine_i32 y, LTEngine_i32 w, LTEngine_i32 h);
void LTENGINE_API LTEngine_Recti_free(LTEngine_HRecti handle);

LTEngine_i32 LTENGINE_API LTEngine_Recti_x(const LTEngine_HRecti handle);
LTEngine_i32 LTENGINE_API LTEngine_Recti_y(const LTEngine_HRecti handle);
LTEngine_i32 LTENGINE_API LTEngine_Recti_w(const LTEngine_HRecti handle);
LTEngine_i32 LTENGINE_API LTEngine_Recti_h(const LTEngine_HRecti handle);

void LTENGINE_API LTEngine_Recti_set_x(LTEngine_HRecti handle, LTEngine_i32 x);
void LTENGINE_API LTEngine_Recti_set_y(LTEngine_HRecti handle, LTEngine_i32 y);
void LTENGINE_API LTEngine_Recti_set_w(LTEngine_HRecti handle, LTEngine_i32 w);
void LTENGINE_API LTEngine_Recti_set_h(LTEngine_HRecti handle, LTEngine_i32 h);

#ifdef __cplusplus
}
#endif


#endif
