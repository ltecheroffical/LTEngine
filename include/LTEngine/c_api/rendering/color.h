#ifndef _LTENGINE_C_API_COLOR_H_
#define _LTENGINE_C_API_COLOR_H_
#ifdef LTENGINE_COMPONENT_C_API

#include <LTEngine/c_api/common/ctypes.h>
#include <LTEngine/common/compiler_utils.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    LTEngine_HANDLE handle;
} LTEngine_HColor;
typedef struct {
    LTEngine_HANDLE handle;
} LTEngine_HColorA;

typedef enum {
    LTENGINE_COLOR_BLACK = 0,
    LTENGINE_COLOR_WHITE,
    LTENGINE_COLOR_RED,
    LTENGINE_COLOR_GREEN,
    LTENGINE_COLOR_BLUE,
    LTENGINE_COLOR_YELLOW,
    LTENGINE_COLOR_CYAN
} LTEngine_ColorDefaults;

typedef enum {
    LTENGINE_COLORA_CLEAR = 0,
    LTENGINE_COLORA_BLACK,
    LTENGINE_COLORA_WHITE,
    LTENGINE_COLORA_RED,
    LTENGINE_COLORA_GREEN,
    LTENGINE_COLORA_BLUE,
    LTENGINE_COLORA_YELLOW,
    LTENGINE_COLORA_CYAN
} LTEngine_ColorADefaults;

LTEngine_HColor LTENGINE_API LTEngine_Color(LTEngine_u8 r, LTEngine_u8 g, LTEngine_u8 b);
LTEngine_HColor LTENGINE_API LTEngine_Color_default(LTEngine_ColorDefaults preset);
void LTENGINE_API LTEngine_Color_free(LTEngine_HColor handle);

LTEngine_u8 LTENGINE_API LTEngine_Color_r(const LTEngine_HColor handle);
LTEngine_u8 LTENGINE_API LTEngine_Color_g(const LTEngine_HColor handle);
LTEngine_u8 LTENGINE_API LTEngine_Color_b(const LTEngine_HColor handle);

void LTENGINE_API LTEngine_Color_setR(LTEngine_HColor handle, LTEngine_u8 r);
void LTENGINE_API LTEngine_Color_setG(LTEngine_HColor handle, LTEngine_u8 g);
void LTENGINE_API LTEngine_Color_setB(LTEngine_HColor handle, LTEngine_u8 b);


LTEngine_HColorA LTENGINE_API LTEngine_ColorA(LTEngine_u8 r, LTEngine_u8 g, LTEngine_u8 b, LTEngine_u8 a);
LTEngine_HColorA LTENGINE_API LTEngine_ColorA_default(LTEngine_ColorADefaults defaultConfig);
void LTENGINE_API LTEngine_ColorA_free(LTEngine_HColorA handle);

LTEngine_u8 LTENGINE_API LTEngine_ColorA_r(const LTEngine_HColorA handle);
LTEngine_u8 LTENGINE_API LTEngine_ColorA_g(const LTEngine_HColorA handle);
LTEngine_u8 LTENGINE_API LTEngine_ColorA_b(const LTEngine_HColorA handle);
LTEngine_u8 LTENGINE_API LTEngine_ColorA_a(const LTEngine_HColorA handle);

void LTENGINE_API LTEngine_ColorA_setR(LTEngine_HColorA handle, LTEngine_u8 r);
void LTENGINE_API LTEngine_ColorA_setG(LTEngine_HColorA handle, LTEngine_u8 g);
void LTENGINE_API LTEngine_ColorA_setB(LTEngine_HColorA handle, LTEngine_u8 b);
void LTENGINE_API LTEngine_ColorA_setA(LTEngine_HColorA handle, LTEngine_u8 a);


#ifdef __cplusplus
}
#endif
#endif
#endif