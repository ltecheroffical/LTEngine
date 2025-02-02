#include <LTEngine/c_api/shapes/rect.h>

#include <LTEngine/shapes/rect.hpp>


LTEngine_HRect LTEngine_Rect_init(LTEngine_f32 x, LTEngine_f32 y, LTEngine_f32 w, LTEngine_f32 h) {
	return new LTEngine::Shapes::Rect(x, y, w, h);
}

void LTEngine_Rect_free(LTEngine_HRect handle) {
	delete (LTEngine::Shapes::Rect *)handle;
}


LTEngine_f32 LTEngine_Rect_x(const LTEngine_HRect handle) {
	return ((LTEngine::Shapes::Rect *)handle)->x;
}

LTEngine_f32 LTEngine_Rect_y(const LTEngine_HRect handle) {
	return ((LTEngine::Shapes::Rect *)handle)->y;
}

LTEngine_f32 LTEngine_Rect_w(const LTEngine_HRect handle) {
	return ((LTEngine::Shapes::Rect *)handle)->w;
}

LTEngine_f32 LTEngine_Rect_h(const LTEngine_HRect handle) {
	return ((LTEngine::Shapes::Rect *)handle)->h;
}


void LTEngine_Rect_setX(LTEngine_HRect handle, LTEngine_f32 x) {
	((LTEngine::Shapes::Rect *)handle)->x = x;
}

void LTEngine_Rect_setY(LTEngine_HRect handle, LTEngine_f32 y) {
	((LTEngine::Shapes::Rect *)handle)->y = y;
}

void LTEngine_Rect_setW(LTEngine_HRect handle, LTEngine_f32 w) {
	((LTEngine::Shapes::Rect *)handle)->w = w;
}

void LTEngine_Rect_setH(LTEngine_HRect handle, LTEngine_f32 h) {
	((LTEngine::Shapes::Rect *)handle)->h = h;
}


LTEngine_HRecti LTEngine_Recti_init(LTEngine_i32 x, LTEngine_i32 y, LTEngine_i32 w, LTEngine_i32 h) {
	return new LTEngine::Shapes::Recti(x, y, w, h);
}

void LTEngine_Recti_free(LTEngine_HRecti handle) {
	delete (LTEngine::Shapes::Recti *)handle;
}


LTEngine_i32 LTEngine_Recti_x(const LTEngine_HRecti handle) {
	return ((LTEngine::Shapes::Recti *)handle)->x;
}

LTEngine_i32 LTEngine_Recti_y(const LTEngine_HRecti handle) {
	return ((LTEngine::Shapes::Recti *)handle)->y;
}

LTEngine_i32 LTEngine_Recti_w(const LTEngine_HRecti handle) {
	return ((LTEngine::Shapes::Recti *)handle)->w;
}

LTEngine_i32 LTEngine_Recti_h(const LTEngine_HRecti handle) {
	return ((LTEngine::Shapes::Recti *)handle)->h;
}


void LTEngine_Recti_setX(LTEngine_HRecti handle, LTEngine_i32 x) {
	((LTEngine::Shapes::Recti *)handle)->x = x;
}

void LTEngine_Recti_setY(LTEngine_HRecti handle, LTEngine_i32 y) {
	((LTEngine::Shapes::Recti *)handle)->y = y;
}

void LTEngine_Recti_setW(LTEngine_HRecti handle, LTEngine_i32 w) {
	((LTEngine::Shapes::Recti *)handle)->w = w;
}

void LTEngine_Recti_setH(LTEngine_HRecti handle, LTEngine_i32 h) {
	((LTEngine::Shapes::Recti *)handle)->h = h;
}
