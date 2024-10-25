#pragma once

#include <LTEngine/math/vec2.h>

#include <LTEngine/common/types/booltypes.h>

#include "colors.h"


typedef struct {
    s32 x, y;
    ltvec2_t zoom;
    bool exclude;

    bool in_use;
} ltrenderer_camera_t;
