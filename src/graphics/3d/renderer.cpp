#include <LTEngine/graphics/3d/renderer.hpp>
#include <LTEngine/exceptions/exc_corrupt_data.hpp>

using namespace LTEngine;
using namespace LTEngine::Graphics;

void Renderer::clear(Color color) {
	clear({color.r, color.g, color.b, 255});
}

void Renderer::set_pixel(Color color, Math::Vec2 position) {
	set_pixel({color.r, color.g, color.b, 255}, position);
}

void Renderer::set_camera(Renderer::Camera &camera) {
    _camera = camera;
}

void Renderer::set_hud_mode(i8 z_order) {
    _hud_mode = true;
    _z_order = z_order;
}

void Renderer::clear_hud_mode() {
    _hud_mode = false;
}


bool Renderer::is_hud_mode() {
    return _hud_mode;
}

i8 Renderer::get_hud_z_order() {
    return _z_order;
}

Math::Vec3 Renderer::world_to_screen_position(Math::Vec3 position) {
    return position - _camera.position;
}

Math::Vec3 Renderer::screen_to_world_position(Math::Vec3 position) {
    return position + _camera.position;
}

u32 Renderer::add_light(Light data) {
    _lights[_next_light_id] = data;
    return _next_light_id++;
}

Renderer::Light Renderer::get_light(u32 light) {
    return _lights.at(light);
}

void Renderer::remove_light(u32 light) {
    _lights.erase(light);
}

std::vector<Renderer::Light> Renderer::get_lights() {
    std::vector<Renderer::Light> lights;

    for (std::pair<u32, Light> pair : _lights) {
        lights.push_back(pair.second);
    }
    return lights;
}


Renderer::Camera Renderer::get_camera() {
    return _camera;
}


