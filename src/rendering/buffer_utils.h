#include <LTEngine/math/vec2.h>

#include <LTEngine/rendering/colors.h>


#ifndef _BUFFER_UTILS_H_
#define _BUFFER_UTILS_H_

void transfer_pixel_to_buffer(ltcolor_t *buffer, ltcolor_t pixel, ltvec2i_t position, u32 width, u32 height);
void transfer_pixela_to_buffer(ltcolor_t *buffer, ltcolora_t pixel, ltvec2i_t position, u32 width, u32 height);

ltcolor_t transfer_buffer_to_pixel(const ltcolor_t *buffer, ltvec2i_t position, u32 width, u32 height);


#endif
