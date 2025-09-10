#ifndef _LTENGINE_3D_RENDERER_HPP_
#define _LTENGINE_3D_RENDERER_HPP_

#include <optional>

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

	struct Material {
		ColorA base_color;
		f32 smoothness;

		Math::Vec2 texture_tiling;
		Math::Vec2 texture_offset;

		std::optional<Image> diffuse_texture;
		std::optional<Image> normal_texture;
		std::optional<Image> specular_texture;
		std::optional<Image> emissive_texture;
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

    // Draws everything on top of everything else
	void set_hud_mode() {
		_hud_mode = true;
	}

	void clear_hud_mode() {
		_hud_mode = false;
	}

  protected:
	bool is_hud_mode() {
		return _hud_mode;
	}

  private:
	bool _hud_mode = false;
};

class IRendererProgrammable {
  public:
	~IRendererProgrammable() = default;

	enum class ShaderType {
		VERTEX = 0,
		FRAGMENT
	};

	virtual u32 create_shader(const char *hlsl_source, ShaderType type) = 0;
	// May throw NotFoundException, InvalidArgumentException
	virtual void delete_shader(u32 shader) = 0;

	virtual u32 create_program() = 0;
	// May throw NotFoundException, InvalidArgumentException
	virtual void add_program_shader(u32 program, u32 shader) = 0;
	// May throw NotFoundException, InvalidArgumentException
	virtual void remove_program_shader(u32 program, u32 shader) = 0;
	// May throw NotFoundException, InvalidArgumentException
	virtual void delete_program(u32 program) = 0;

	// May throw NotFoundException, InvalidArgumentException
	virtual void use_program(u32 program) = 0;
	virtual void reset_program() = 0;
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
