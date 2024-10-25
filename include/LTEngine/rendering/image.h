#include <LTEngine/common/types/inttypes.h>
#include <LTEngine/common/types/booltypes.h>

#include <LTEngine/rendering/colors.h>


typedef struct {
    u32 _width, _height;

    ltcolora_t *_pixels;
} ltimage_t;


ltimage_t ltimage_new(u32 width, u32 height);
// Creates a texture from a RGBA pixel buffer
ltimage_t ltimage_from_buffer(ltcolora_t *buffer, u32 width, u32 height);
void ltimage_free(ltimage_t *texture);

void ltimage_resize(ltimage_t *texture, u32 width, u32 height);
void ltimage_query_size(const ltimage_t *texture, u32 *width, u32 *height);

void ltimage_fliph(ltimage_t *texture);
void ltimage_flipv(ltimage_t *texture);

void ltimage_set_pixel(ltimage_t *texture, ltcolora_t color, u32 x, u32 y);
ltcolora_t ltimage_get_pixel(const ltimage_t *texture, u32 x, u32 y);

// Loads an image from a file, if not in RGBA format, it will convert it
bool ltimage_load_image(ltimage_t *texture, const char *path);
// Does the same thing as `texture_load_image` but from a memory buffer
bool ltimage_load_image_from_memory(ltimage_t *texture, const u8 *buffer, u32 size);
