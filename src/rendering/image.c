#include <stdlib.h>
#include <string.h>

#include <stb_image/stb_image.h>
#include <stb_image/stb_image_write.h>

#include <LTEngine/rendering/image.h>


ltimage_t ltimage_new(u32 width, u32 height) {
    ltimage_t texture;
    texture._width = width;
    texture._height = height;
    
    texture._pixels = (ltcolora_t*)malloc(width * height * sizeof(ltcolora_t));
    return texture;
}

ltimage_t ltimage_from_buffer(const ltcolor_t *buffer, u32 width, u32 height) {
    ltimage_t texture = ltimage_new(width, height);
    
    for (u32 y = 0; y < height; y++) {
        for (u32 x = 0; x < width; x++) {
            texture._pixels[y * width + x] = ltcolora_from(buffer[y * width + x]);
        }
    }

    return texture;
}

ltimage_t ltimage_from_buffera(const ltcolora_t *buffer, u32 width, u32 height) {
    ltimage_t texture = ltimage_new(width, height);
    memcpy(texture._pixels, buffer, width * height * sizeof(ltcolora_t));
    return texture;
}

void ltimage_free(ltimage_t *texture) {
    free(texture->_pixels);
}


void ltimage_resize(ltimage_t *texture, u32 width, u32 height) {
    ltcolora_t *pixels = (ltcolora_t*)realloc(texture->_pixels, width * height * sizeof(ltcolora_t));
    if (pixels == NULL) {
        return;
    }

    texture->_pixels = pixels;
    texture->_height = height;
    texture->_width = width;
}

void ltimage_query_size(const ltimage_t *texture, u32 *width, u32 *height) {
    *width = texture->_width;
    *height = texture->_height;
}


void ltimage_fliph(ltimage_t *texture) {
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

void ltimage_flipv(ltimage_t *texture) {
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


void ltimage_set_pixel(ltimage_t *texture, ltcolora_t color, u32 x, u32 y) {
    texture->_pixels[y * texture->_width + x] = color;
}

ltcolora_t ltimage_get_pixel(const ltimage_t *texture, u32 x, u32 y) {
    return texture->_pixels[y * texture->_width + x];
}


bool ltimage_load_image(ltimage_t *texture, const char *path) {
    s32 width, height, c;
    u8 *pixels = stbi_load(path, &width, &height, &c, 0);
    if (pixels == NULL) {
        return false;
    }

    ltimage_resize(texture, width, height);

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


bool ltimage_save_image_png(ltimage_t *texture, const char *path) {
    stbi_write_png(path, texture->_width, texture->_height, 4, texture->_pixels, texture->_width * 4);
    return true;
}
