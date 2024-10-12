#include <stdlib.h>

#include <LTEngine/rendering/rendering.h>
#include <LTEngine/rendering/colors.h>


u32 ltrenderer_create_camera(ltrenderer_t *renderer, ltvec2_t position, ltvec2_t zoom) {
    ltrenderer_camera_t *camera = &renderer->_cams.cams[0];
    bool camera_selected = false;

    while (camera < &renderer->_cams.cams[renderer->_cams.size]) {
        if (!camera->in_use) {
            camera_selected = true;
            break;
        }
        camera++;
    }
   
    if (!camera_selected) {
        ltrenderer_camera_t *new_cams = realloc(renderer->_cams.cams, renderer->_cams.size * sizeof(ltrenderer_camera_t));
        if (new_cams == NULL) {
            return 0;
        }
        renderer->_cams.cams = new_cams;
        renderer->_cams.size *= 2;
    }
        
    camera->x = position.x;
    camera->y = position.y;
    camera->zoom = zoom;
    camera->pixels = (ltcolor_t*)malloc(renderer->_width * renderer->_height * sizeof(ltcolor_t));
    camera->exclude = false;
    camera->in_use = true;

    if (camera->pixels == NULL) {
        camera->in_use = false;
        return 0;
    }

    return (u32)(camera - renderer->_cams.cams);
}

void ltrenderer_destroy_camera(ltrenderer_t *renderer, u32 index) {
    if (renderer->_cams.size < index) {
        return;
    }

    renderer->_cams.cams[index].in_use = false;

    free(renderer->_cams.cams[index].pixels);
}


ltvec2i_t ltrenderer_get_camera_position(const ltrenderer_t *renderer, u32 index) {
    if (renderer->_cams.size < index) {
        return LTVEC2I_ZERO;
    }
    return (ltvec2i_t){renderer->_cams.cams[index].x, renderer->_cams.cams[index].y};
}

ltvec2_t ltrenderer_get_camera_zoom(const ltrenderer_t *renderer, u32 index) {
    if (renderer->_cams.size < index) {
        return LTVEC2_ZERO;
    }
    return renderer->_cams.cams[index].zoom;
}
