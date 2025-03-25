#ifdef LTENGINE_COMPONENT_C_API
#include <LTEngine/c_api/shapes/rect.h>

#include <LTEngine/shapes/rect.hpp>


LTEngine_HRect LTEngine_Rect(LTEngine_f32 x, LTEngine_f32 y, LTEngine_f32 w, LTEngine_f32 h) {
	return {{new LTEngine::Shapes::Rect(x, y, w, h)}};
}

void LTEngine_Rect_free(LTEngine_HRect handle) {
	delete (LTEngine::Shapes::Rect *)handle.handle.ptr;
}


LTEngine_f32 LTEngine_Rect_w(const LTEngine_HRect handle) {
	return ((LTEngine::Shapes::Rect *)handle.handle.ptr)->w;
}

LTEngine_f32 LTEngine_Rect_h(const LTEngine_HRect handle) {
	return ((LTEngine::Shapes::Rect *)handle.handle.ptr)->h;
}


void LTEngine_Rect_setW(LTEngine_HRect handle, LTEngine_f32 w) {
	((LTEngine::Shapes::Rect *)handle.handle.ptr)->w = w;
}

void LTEngine_Rect_setH(LTEngine_HRect handle, LTEngine_f32 h) {
	((LTEngine::Shapes::Rect *)handle.handle.ptr)->h = h;
}


LTEngine_HRecti LTEngine_Recti(LTEngine_i32 x, LTEngine_i32 y, LTEngine_u32 w, LTEngine_u32 h) {
	return {{new LTEngine::Shapes::Recti(x, y, w, h)}};
}

void LTEngine_Recti_free(LTEngine_HRecti handle) {
	delete (LTEngine::Shapes::Recti *)handle.handle.ptr;
}


LTEngine_u32 LTEngine_Recti_w(const LTEngine_HRecti handle) {
	return ((LTEngine::Shapes::Recti *)handle.handle.ptr)->w;
}

LTEngine_u32 LTEngine_Recti_h(const LTEngine_HRecti handle) {
	return ((LTEngine::Shapes::Recti *)handle.handle.ptr)->h;
}


void LTEngine_Recti_setW(LTEngine_HRecti handle, LTEngine_u32 w) {
	((LTEngine::Shapes::Recti *)handle.handle.ptr)->w = w;
}

void LTEngine_Recti_setH(LTEngine_HRecti handle, LTEngine_u32 h) {
	((LTEngine::Shapes::Recti *)handle.handle.ptr)->h = h;
}

#endif
