#pragma once

#include <LTEngine/structure/object_structure.hpp>

#include "paddle_controller.hpp"


namespace Pong {
    class Paddle : public LTEngine::Object::ObjectStructure::Object {
    public:
        Paddle(PaddleController *controller);
        ~Paddle() override = default;

        const static u32 PADDLE_WIDTH = 8;
        const static u32 PADDLE_HEIGHT = 75;

        void update(f32 delta) override;
        void render(LTEngine::Rendering::Renderer *renderer) override;

        std::unique_ptr<Object> clone() const override;

    private:
        constexpr static f32 PADDLE_SPEED = 450.f;

        PaddleController *m_controller;
    };
}
