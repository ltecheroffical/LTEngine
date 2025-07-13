#include <stb_image/stb_image.h>
#include <stb_image/stb_image_write.h>

#include <LTEngine/graphics/image.hpp>


using namespace LTEngine;
using namespace LTEngine::Graphics;


Image::Image(u32 width, u32 height) : _width(width), _height(height) {
    _data.resize(width * height);
}

Image::Image(const Color *buffer, u32 width, u32 height) : Image(width, height) {
    for (u32 y = 0; y < height; y++) {
        for (u32 x = 0; x < width; x++) {
            _data.at(y * width + x).r = buffer[y * width + x].r;
            _data.at(y * width + x).g = buffer[y * width + x].g;
            _data.at(y * width + x).b = buffer[y * width + x].b;
            _data.at(y * width + x).a = 255;
        }
    }
}

Image::Image(const ColorA *buffer, u32 width, u32 height) : Image(width, height) {
    for (u32 y = 0; y < height; y++) {
        for (u32 x = 0; x < width; x++) {
            _data.at(y * width + x) = buffer[y * width + x];
        }
    }
}


void Image::set_size(u32 width, u32 height) {
    _width = width;
    _height = height;
    _data.resize(width * height);
}

Math::Vec2u Image::get_size() const {
    return Math::Vec2u(_width, _height);
}


void Image::set_pixel(ColorA color, u32 x, u32 y) {
    _data.at(y * _width + x) = color;
}

ColorA Image::get_pixel(u32 x, u32 y) const {
    return _data.at(y * _width + x);
}


void Image::flip_h() {
    for (u32 y = 0; y < _height / 2; y++) {
        for (u32 x = 0; x < _width; x++) {
            ColorA temp = _data.at(y * _width + x);
            _data.at(y * _width + x) = _data.at((_height - y - 1) * _width + x);
            _data.at((_height - y - 1) * _width + x) = temp;
        }
    }
}

void Image::flip_v() {
    for (u32 y = 0; y < _height; y++) {
        for (u32 x = 0; x < _width / 2; x++) {
            ColorA temp = _data.at(y * _width + x);
            _data.at(y * _width + x) = _data.at(y * _width + _width - x - 1);
            _data.at(y * _width + _width - x - 1) = temp;
        }
    }
}


void Image::load(const char *filename) {
    int channels_in_file = 0;
    int width, height = 0;
    u8 *data = stbi_load(filename, &width, &height, &channels_in_file, 4);

    _width = width;
    _height = height;

    if (data == nullptr) {
        throw std::runtime_error("Failed to load image: " + std::string(filename));
    }

    _data.resize(_width * _height);
    for (u32 y = 0; y < height; y++) {
        for (u32 x = 0; x < _width; x++) {
            _data.at(y * _width + x).r = data[(y * _width + x) * 4 + 0];
            _data.at(y * _width + x).g = data[(y * _width + x) * 4 + 1];
            _data.at(y * _width + x).b = data[(y * _width + x) * 4 + 2];
            _data.at(y * _width + x).a = data[(y * _width + x) * 4 + 3];
        }
    }
    stbi_image_free(data);
}

void Image::load(u8 *buffer, size_t size) {
    int channels_in_file = 0;
    int width, height = 0;
    u8 *data = stbi_load_from_memory(buffer, size, &width, &height, &channels_in_file, 4);
    
    _width = width;
    _height = height;

    if (data == nullptr) {
        throw std::runtime_error("Failed to load image from memory");
    }

    _data.resize(_width * _height);
    for (u32 y = 0; y < height; y++) {
        for (u32 x = 0; x < _width; x++) {
            _data.at(y * _width + x).r = data[(y * _width + x) * 4 + 0];
            _data.at(y * _width + x).g = data[(y * _width + x) * 4 + 1];
            _data.at(y * _width + x).b = data[(y * _width + x) * 4 + 2];
            _data.at(y * _width + x).a = data[(y * _width + x) * 4 + 3];
        }
    }
    stbi_image_free(data);
}


void Image::save_png(const char *filename) const {
    stbi_write_png(filename, _width, _height, 4, _data.data(), _width * 4);
}

void Image::save_bmp(const char *filename) const {
    stbi_write_bmp(filename, _width, _height, 4, _data.data());
}

void Image::save_jpg(const char *filename) const {
    stbi_write_jpg(filename, _width, _height, 4, _data.data(), 100);
}

std::vector<u8> Image::save_png() const {
    std::vector<u8> data;
    stbi_write_png_to_func([](void *context, void *data, int size) {
        auto array = (std::vector<u8>*)data;
        array->resize(size);
        std::memcpy(array->data(), (u8*)data, size);
    }, &data, _width, _height, 4, _data.data(), _width * 4);
    return data;
}

std::vector<u8> Image::save_bmp() const {
    std::vector<u8> data;
    stbi_write_bmp_to_func([](void *context, void *data, int size) {
        auto array = (std::vector<u8>*)data;
        array->resize(size);
        std::memcpy(array->data(), (u8*)data, size);
    }, &data, _width, _height, 4, _data.data());
    return data;
}

std::vector<u8> Image::save_jpg() const {
    std::vector<u8> data;
    stbi_write_jpg_to_func([](void *context, void *data, int size) {
        auto array = (std::vector<u8>*)data;
        array->resize(size);
        std::memcpy(array->data(), (u8*)data, size);
    }, &data, _width, _height, 4, _data.data(), _width * 4);
    return data;
}
