#include <stb_image/stb_image.h>
#include <stb_image/stb_image_write.h>

#include <LTEngine/rendering/image.hpp>


using namespace LTEngine;
using namespace LTEngine::Rendering;


Image::Image(u32 width, u32 height) : m_width(width), m_height(height) {
    m_data.resize(width * height);
}

Image::Image(const Color *buffer, u32 width, u32 height) : Image(width, height) {
    for (u32 y = 0; y < height; y++) {
        for (u32 x = 0; x < width; x++) {
            m_data.at(y * width + x).r = buffer[y * width + x].r;
            m_data.at(y * width + x).g = buffer[y * width + x].g;
            m_data.at(y * width + x).b = buffer[y * width + x].b;
            m_data.at(y * width + x).a = 255;
        }
    }
}

Image::Image(const ColorA *buffer, u32 width, u32 height) : Image(width, height) {
    for (u32 y = 0; y < height; y++) {
        for (u32 x = 0; x < width; x++) {
            m_data.at(y * width + x) = buffer[y * width + x];
        }
    }
}


void Image::setSize(u32 width, u32 height) {
    m_width = width;
    m_height = height;
    m_data.resize(width * height);
}

Math::Vec2u Image::getSize() const {
    return Math::Vec2u(m_width, m_height);
}


void Image::setPixel(ColorA color, u32 x, u32 y) {
    m_data.at(y * m_width + x) = color;
}

ColorA Image::getPixel(u32 x, u32 y) const {
    return m_data.at(y * m_width + x);
}


void Image::flipH() {
    for (u32 y = 0; y < m_height / 2; y++) {
        for (u32 x = 0; x < m_width; x++) {
            ColorA temp = m_data.at(y * m_width + x);
            m_data.at(y * m_width + x) = m_data.at((m_height - y - 1) * m_width + x);
            m_data.at((m_height - y - 1) * m_width + x) = temp;
        }
    }
}

void Image::flipV() {
    for (u32 y = 0; y < m_height; y++) {
        for (u32 x = 0; x < m_width / 2; x++) {
            ColorA temp = m_data.at(y * m_width + x);
            m_data.at(y * m_width + x) = m_data.at(y * m_width + m_width - x - 1);
            m_data.at(y * m_width + m_width - x - 1) = temp;
        }
    }
}


void Image::load(const char *filename) {
    int channels_in_file = 0;
    int width, height = 0;
    u8 *data = stbi_load(filename, &width, &height, &channels_in_file, 4);

    m_width = width;
    m_height = height;

    if (data == nullptr) {
        throw std::runtime_error("Failed to load image: " + std::string(filename));
    }

    m_data.resize(m_width * m_height);
    for (u32 y = 0; y < m_height; y++) {
        for (u32 x = 0; x < m_width; x++) {
            m_data.at(y * m_width + x).r = data[(y * m_width + x) * 4 + 0];
            m_data.at(y * m_width + x).g = data[(y * m_width + x) * 4 + 1];
            m_data.at(y * m_width + x).b = data[(y * m_width + x) * 4 + 2];
            m_data.at(y * m_width + x).a = data[(y * m_width + x) * 4 + 3];
        }
    }
    stbi_image_free(data);
}

void Image::load(u8 *buffer, u32 size) {
    int channels_in_file = 0;
    int width, height = 0;
    u8 *data = stbi_load_from_memory(buffer, size, &width, &height, &channels_in_file, 4);
    
    m_width = width;
    m_height = height;

    if (data == nullptr) {
        throw std::runtime_error("Failed to load image from memory");
    }

    m_data.resize(m_width * m_height);
    for (u32 y = 0; y < m_height; y++) {
        for (u32 x = 0; x < m_width; x++) {
            m_data.at(y * m_width + x).r = data[(y * m_width + x) * 4 + 0];
            m_data.at(y * m_width + x).g = data[(y * m_width + x) * 4 + 1];
            m_data.at(y * m_width + x).b = data[(y * m_width + x) * 4 + 2];
            m_data.at(y * m_width + x).a = data[(y * m_width + x) * 4 + 3];
        }
    }
    stbi_image_free(data);
}


void Image::savePNG(const char *filename) const {
    stbi_write_png(filename, m_width, m_height, 4, m_data.data(), m_width * 4);
}

void Image::saveBMP(const char *filename) const {
    stbi_write_bmp(filename, m_width, m_height, 4, m_data.data());
}

void Image::saveJPG(const char *filename) const {
    stbi_write_jpg(filename, m_width, m_height, 4, m_data.data(), 100);
}
