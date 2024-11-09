#pragma once

#include <LTEngine/window.hpp>

#include "paddle_controller.hpp"


namespace Pong {
    class PlayerController : public PaddleController {
    public:
        PlayerController(LTEngine::Window *window) : m_window(window) {}
        ~PlayerController() override = default;

        i32 getDirection() override;

    private:
        LTEngine::Window *m_window;
    };
}
