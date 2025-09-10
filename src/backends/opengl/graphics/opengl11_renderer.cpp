#ifdef LTENGINE_COMPONENT_OPENGL

#include <LTEngine/backends/opengl/graphics/opengl11_renderer.hpp>

using namespace LTEngine;
using namespace LTEngine::Graphics;

void OpenGL11Renderer3D::clear(ColorA color) {
    _add_draw_cmd([color]() {
        glClearColor(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }, -1);
}

void OpenGL11Renderer3D::set_pixel(ColorA pixel, Math::Vec2 position) {
    _add_draw_cmd([pixel, position, hud_mode = is_hud_mode(), this]() {
        glDisable(GL_DEPTH_TEST);

        glColor4f(pixel.r / 255.f, pixel.g / 255.f, pixel.b / 255.f, pixel.a / 255.f);
        Math::Vec2 ndc = _to_ndc2d(position);
        glVertex2f(ndc.x, ndc.y);
    }, GL_POINT);
}

#endif // LTENGINE_COMPONENT_OPENGL
