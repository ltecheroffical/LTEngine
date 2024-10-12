#include <stdlib.h>
#include <string.h>

#include <stb_image/stb_image.h>

#include <LTEngine/rendering/cpu_texture.h>


lttexture_cpu_t lttexture_cpu_new(u32 width, u32 height) {
    lttexture_cpu_t texture;
    texture._width = width;
    texture._height = height;
    
    texture._pixels = (ltcolora_t*)malloc(width * height * sizeof(ltcolora_t));
    return texture;
}

lttexture_cpu_t lttexture_cpu_from_buffer(ltcolora_t *buffer, u32 width, u32 height) {
    lttexture_cpu_t texture = lttexture_cpu_new(width, height);
    memcpy(texture._pixels, buffer, width * height * sizeof(ltcolora_t));
    return texture;
}

void lttexture_cpu_free(lttexture_cpu_t *texture) {
    free(texture->_pixels);
}


void lttexture_cpu_resize(lttexture_cpu_t *texture, u32 width, u32 height) {
    ltcolora_t *pixels = (ltcolora_t*)realloc(texture->_pixels, width * height * sizeof(ltcolora_t));
    if (pixels == NULL) {
        return;
    }

    texture->_pixels = pixels;
    texture->_height = height;
    texture->_width = width;
}

void lttexture_cpu_query_size(const lttexture_cpu_t *texture, u32 *width, u32 *height) {
    *width = texture->_width;
    *height = texture->_height;
}


void lttexture_cpu_fliph(lttexture_cpu_t *texture) {
    for (u32 y = 0; y < texture->_height; y++) {
        for (u32 x = 0; x < texture->_width / 2; x++) {
            u32 left_index = y * texture->_width + x;
            u32 right_index = y * texture->_width + (texture->_width - 1 - x);

            ltcolora_t tmp = texture->_pixels[left_index];
            texture->_pixels[left_index] = texture->_pixels[right_index];
            texture->_pixels[right_index] = tmp;
        }
    }
}

void lttexture_cpu_flipv(lttexture_cpu_t *texture) {
    for (u32 y = 0; y < texture->_height / 2; y++) {
        for (u32 x = 0; x < texture->_width; x++) {
            u32 top_index = y * texture->_width + x;
            u32 bottom_index = (texture->_height - 1 - y) * texture->_width + x;

            ltcolora_t tmp = texture->_pixels[top_index];
            texture->_pixels[top_index] = texture->_pixels[bottom_index];
            texture->_pixels[bottom_index] = tmp;
        }
    }
}


void lttexture_cpu_set_pixel(lttexture_cpu_t *texture, ltcolora_t color, u32 x, u32 y) {
    texture->_pixels[y * texture->_width + x] = color;
}

ltcolora_t lttexture_cpu_get_pixel(const lttexture_cpu_t *texture, u32 x, u32 y) {
    return texture->_pixels[y * texture->_width + x];
}


bool lttexture_cpu_load_image(lttexture_cpu_t *texture, const char *path) {
    i32 width, height, c;
    u8 *pixels = stbi_load(path, &width, &height, &c, 0);
    if (pixels == NULL) {
        return false;
    }

    lttexture_cpu_resize(texture, width, height);

    for (u32 y = 0; y < height; y++) {
        for (u32 x = 0; x < width; x++) {
            u32 index = y * width + x;
            if (c > 3) {
                texture->_pixels[index].a = pixels[index * c + 3];
            } else {
                texture->_pixels[index].a = 255;
            }
            texture->_pixels[index].r = pixels[index * c + 0];
            texture->_pixels[index].g = pixels[index * c + 1];
            texture->_pixels[index].b = pixels[index * c + 2];
        }
    }
    stbi_image_free(pixels);
    return true;
}
