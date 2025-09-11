#ifndef _LTENGINE_3D_RENDERER_HPP_
#define _LTENGINE_3D_RENDERER_HPP_

#include <optional>
#include <unordered_map>

#include <LTEngine/math/vec3.hpp>

#include <LTEngine/os/mem_file.hpp>

#include <LTEngine/exceptions/exc_corrupt_data.hpp>

#include <LTEngine/shapes/3d/capsule.hpp>
#include <LTEngine/shapes/3d/cube.hpp>
#include <LTEngine/shapes/3d/cylinder.hpp>
#include <LTEngine/shapes/3d/polyhedron.hpp>
#include <LTEngine/shapes/3d/sphere.hpp>
#include <LTEngine/shapes/3d/torus.hpp>

#include <LTEngine/graphics/3d/3d_model.hpp>

#include <LTEngine/graphics/image.hpp>

namespace LTEngine::Graphics {
class LTENGINE_API Renderer {
public:
	virtual ~Renderer() = default;

    enum class TextureScaleMode {
        Linear = 0,
        Nearest,
        Repeat,
        MirroredRepeat,
        ClampToEdge,
    };


	struct Material {
		ColorA base_color;
		f32 smoothness;

		Math::Vec2 texture_tiling;
		Math::Vec2 texture_offset;

        TextureScaleMode diffuse_texture_scale_mode;
        std::optional<Image> diffuse_texture;
	};

    struct Light {
        enum class Type {
            Directional,
            Point,
            Spot
        };

        Type type = Type::Point;

        Math::Vec3 position = {0, 0, 0};  // for point/spot
        Math::Vec3 direction = {0, 0, -1}; // for directional/spot

        ColorA color = {255, 255, 255, 255}; // diffuse color
        ColorA ambient = {51, 51, 51, 255};
        ColorA specular = {255, 255, 255, 255};

        float intensity = 1.0f; // global multiplier
        float cutoff_angle = 45.0f; // for spotlights
    };

    struct Camera {
        Math::Vec3 position;
        Math::Vec3 rotation;
        f32 zoom;
        f32 fov;

        enum class Prespective {
            Projection = 0,
            Ortho
        } prespective;
    };

	void clear(Color color);
	virtual void clear(ColorA color) = 0;

	void set_pixel(Color pixel, Math::Vec2 position);
	virtual void set_pixel(ColorA pixel, Math::Vec2 position) = 0;

	virtual void draw(Shapes::Cube cube, Math::Vec3 scale, Material &material) = 0;
	virtual void draw(Shapes::Sphere sphere, Math::Vec3 scale, Material &material) = 0;
	virtual void draw(Shapes::Cylinder cylinder, Math::Vec3 scale, Material &material) = 0;
	virtual void draw(Shapes::Capsule capsule, Math::Vec3 scale, Material &material) = 0;
	virtual void draw(Shapes::Torus torus, Math::Vec3 scale, Material &material) = 0;
	virtual void draw(Shapes::Polyhedron polyhedron, Math::Vec3 scale, Material &material) = 0;

	virtual void draw(Model3D model, Math::Vec3 position, Math::Vec3 rotation, Math::Vec3 scale, Material &material) = 0;

    void set_camera(Renderer::Camera &camera);

    // Draws everything on top of everything else
	void set_hud_mode(i8 z_order);
	void clear_hud_mode();

    Math::Vec3 world_to_screen_position(Math::Vec3 position);
    Math::Vec3 screen_to_world_position(Math::Vec3 position);

    u32 add_light(Light data);
    Light get_light(u32 light);
    void remove_light(u32 light);


protected:
    Camera get_camera();

	bool is_hud_mode();
    i8 get_hud_z_order();

    std::vector<Light> get_lights();

private:
	bool _hud_mode;
    i8 _z_order;

    Camera _camera;

    std::unordered_map<u32, Light> _lights;

    u32 _next_light_id = 0;
};

// color = (A - B) * C + D
class IRendererBasicShaders {
  public:
	~IRendererBasicShaders() = default;

    struct ShaderInput {
        enum class Type {
            StageOutputN = 0, // Input: size_t, Takes the stage output of an index as an offset
            StageOutputBackwardsOffsetN, // Input: size_t, Takes the stage output of a backwards offset from the current stage, backwards offset 0 defaults to offset by -1
            Color, // Input: ColorA, Constant or Runtime color
            TextureColor, // Texture Color at the same pixel being rendered wrapping, Input: u8
            
            Material_DiffuseTexture, // Diffuse Texture of material or white
            Material_BaseColor,
            
            Builtin_RandomColor, // Random Color
            Builtin_FrameRandomColor, // Random Color Per Frame
            Builtin_Timer, // Timer incrementing every ms mod 256
        };

        union {
            ColorA colora;
            Color color;

            u8 u8;
            u16 u16;
            i8 i8;
            i16 i16;

            size_t size;
            ssize_t ssize;
        } input;
    };

    struct ShaderStage {
        ShaderInput A;
        ShaderInput B;
        ShaderInput C;
        ShaderInput D;
    };

    struct Shader {
        // Last stage is output
        std::vector<ShaderStage> stages;
    };

    void use_shader(Shader shader, std::vector<Image> textures);
    void reset_shader();
};

class IRendererFramebufferOutput {
  public:
	/*
	 * @param screen If not null, outputs display to it
	 *
	 * @returns The size of the display output
	 */
	virtual size_t output(const Color *screen) = 0;
};
} // namespace LTEngine::Graphics

#endif // _LTENGINE_3D_RENDERER_HPP_
