#include "buffer_utils.h"


void transfer_pixel_to_buffer(ltcolor_t *buffer, ltcolor_t pixel, ltvec2i_t position, u32 width, u32 height) {
    buffer[position.y * width + position.x] = pixel;
}

void transfer_pixela_to_buffer(ltcolor_t *buffer, ltcolora_t pixel, ltvec2i_t position, u32 width, u32 height) {
    ltcolor_t bg = buffer[position.y * width + position.x];
        
    f32 A_n = pixel.a / 255.0f;

    buffer[position.y * width + position.x] = ltcolor_add(
                ltcolor_mulf(ltcolor_fromA(pixel), A_n),
                ltcolor_mulf(bg, (1 - A_n)));
}


ltcolor_t transfer_buffer_to_pixel(const ltcolor_t *buffer, ltvec2i_t position, u32 width, u32 height) {
    return buffer[position.y * width + position.x];
}
