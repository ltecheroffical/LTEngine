#include <LTEngine/common/types/inttypes.h>
#include <LTEngine/common/types/booltypes.h>

#include <LTEngine/rendering/colors.h>


#ifndef _LTTEXTURE_H_
#define _LTTEXTURE_H_

typedef struct {
    u32 _width, _height;

    ltcolora_t *_pixels;
} lttexture_cpu_t;


lttexture_cpu_t lttexture_cpu_new(u32 width, u32 height);
// Creates a texture from a RGBA pixel buffer
lttexture_cpu_t lttexture_cpu_from_buffer(ltcolora_t *buffer, u32 width, u32 height);
void lttexture_cpu_free(lttexture_cpu_t *texture);

void lttexture_cpu_resize(lttexture_cpu_t *texture, u32 width, u32 height);
void lttexture_cpu_query_size(const lttexture_cpu_t *texture, u32 *width, u32 *height);

void lttexture_cpu_fliph(lttexture_cpu_t *texture);
void lttexture_cpu_flipv(lttexture_cpu_t *texture);

void lttexture_cpu_set_pixel(lttexture_cpu_t *texture, ltcolora_t color, u32 x, u32 y);
ltcolora_t lttexture_cpu_get_pixel(const lttexture_cpu_t *texture, u32 x, u32 y);

// Loads an image from a file, if not in RGBA format, it will convert it
bool lttexture_cpu_load_image(lttexture_cpu_t *texture, const char *path);
// Does the same thing as `texture_load_image` but from a memory buffer
bool lttexture_cpu_load_image_from_memory(lttexture_cpu_t *texture, const u8 *buffer, u32 size);

#endif
