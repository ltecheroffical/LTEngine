#include <LTEngine/rendering/software_renderer.hpp>


using namespace LTEngine;
using namespace LTEngine::Rendering;


SoftwareRenderer::SoftwareRenderer(u32 width, u32 height) : m_screenWidth(width), m_screenHeight(height) {
    m_screen.resize(m_screenWidth * m_screenHeight);
}


void SoftwareRenderer::resize(u32 width, u32 height) {
    m_screenWidth = width;
    m_screenHeight = height;
    m_screen.resize(m_screenWidth * m_screenHeight);
}


u32 SoftwareRenderer::getScreenData(Color *data) {
    if (data != nullptr) {
        memcpy(data, m_screen.data(), sizeof(Color) * m_screenWidth * m_screenHeight);
    }
    return m_screen.size() * sizeof(Color);
}


void SoftwareRenderer::clear(Color color) {
    std::fill(m_screen.begin(), m_screen.end(), color);
}

void SoftwareRenderer::clear(ColorA color) {
    std::transform(m_screen.begin(), m_screen.end(), m_screen.begin(), [color](Color c) {
        const f32 A_n = color.a / 255.f;
        return Color(color.r * A_n, color.g * A_n, color.b * A_n) + (c * (1.f - A_n));
    });
}
