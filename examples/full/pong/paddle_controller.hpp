#pragma once

#include <LTEngine/common/types/inttypes.h>


namespace Pong {
    class PaddleController {
    public:
        virtual ~PaddleController() = default;

        virtual i32 getDirection() = 0;
    };
}
