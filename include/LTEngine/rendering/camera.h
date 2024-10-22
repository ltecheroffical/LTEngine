#pragma once

#include <LTEngine/math/vec2.h>

#include <LTEngine/common/types/booltypes.h>

#include "colors.h"


typedef struct {
    s32 x, y;
    ltvec2_t zoom;
    bool exclude;

    ltcolor_t *pixels;

    bool in_use;
} ltrenderer_camera_t;
