#pragma once

#include <vector>

#include <LTEngine/common/types/inttypes.h>
#include <LTEngine/common/types/floattypes.h>

#include <LTEngine/math/vec2.hpp>
#include <LTEngine/math/rect.hpp>

#include <LTEngine/rendering/color.hpp>
#include <LTEngine/rendering/image.hpp>
#include <LTEngine/rendering/camera.hpp>


namespace LTEngine::Rendering {
    typedef u16 ltrenderer_flags_t;

    class ltrenderer_t {
    public:
        virtual ~ltrenderer_t() = 0;

        void set_scale(Math::ltvec2_t scale);
        void set_rotation(f32 rotation);

        void set_z_order(u16 z);

        void set_scale_factor(f32 scale);
        void set_rotation_offset(f32 offset);

        void set_iris_mode();
        void clear_iris_mode();

        u32 create_camera(Math::ltvec2_t position, Math::ltvec2_t zoom);
        void delete_camera(u32 id);
        void set_camera_position(u32 id, Math::ltvec2_t position);
        void set_camera_rotation(u32 id, f32 rotation);
        void set_camera_zoom(u32 id, Math::ltvec2_t zoom);
        void set_camera_include(u32 id);
        void set_camera_exclude(u32 id);
        Math::ltvec2_t get_camera_position(u32 id) const;
        Math::ltvec2_t get_camera_zoom(u32 id) const;
        f32 get_camera_rotation(u32 id) const;

        virtual u32 get_screen_data(ltcolor_t *data, u32 width, u32 height) = 0;
        virtual u32 get_screen_data(ltcolora_t *data, u32 width, u32 height);

        virtual void clear(ltcolor_t color) = 0;
        virtual void clear(ltcolora_t color) = 0;

        virtual void set_pixel(Math::ltvec2i_t position, ltcolor_t color) = 0;
        virtual void set_pixel(Math::ltvec2i_t position, ltcolora_t color) = 0;
        virtual ltcolor_t get_pixel(Math::ltvec2i_t position) = 0;

        virtual void draw_rect(Math::ltrect_t rect, ltcolora_t color, ltrenderer_flags_t flags) = 0;
        virtual void draw_circle(Math::ltvec2i_t position, u32 radius, ltcolora_t color, ltrenderer_flags_t flags) = 0;
        void draw_triangle(Math::ltvec2_t a, Math::ltvec2_t b, Math::ltvec2_t c, ltcolora_t color, ltrenderer_flags_t flags);

        virtual void draw_line(Math::ltvec2i_t a, Math::ltvec2i_t b, u16 thickness, ltcolora_t color, ltrenderer_flags_t flags) = 0;
        virtual void draw_points(const Math::ltvec2_t *points, u32 count, ltcolora_t color, ltrenderer_flags_t flags) = 0;

        virtual void draw_image(const ltimage_t *image, Math::ltvec2i_t position, ltcolora_t color, ltrenderer_flags_t flags) = 0;
        virtual void draw_camera(u32 id, Math::ltrecti_t rect, ltcolora_t color, ltrenderer_flags_t flags) = 0;

    protected:
        Math::ltvec2_t _scale;
        f32 _rotation;

        u16 _z_order;

        bool _iris_mode:1;

    private:
        Math::ltvec2_t _scale_factor[2];
        f32 _rotation_offset[2];

        std::vector<ltcamera_t> _cameras;
    };
}
