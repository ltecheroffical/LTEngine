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
		ColorA baseColor;
		f32 smoothness;

		Math::Vec2 textureTiling;
		Math::Vec2 textureOffset;

		std::optional<Image> diffuseTexture;
		std::optional<Image> normalTexture;
		std::optional<Image> specularTexture;
		std::optional<Image> emissiveTexture;
	};

	void clear(Color color);
	virtual void clear(ColorA color) = 0;

	void setPixel(Color pixel, Math::Vec2 position);
	virtual void setPixel(ColorA pixel, Math::Vec2 position) = 0;

	virtual void draw(Shapes::Cube cube, Math::Vec3 scale, Material &material) = 0;
	virtual void draw(Shapes::Sphere sphere, Math::Vec3 scale, Material &material) = 0;
	virtual void draw(Shapes::Cylinder cylinder, Math::Vec3 scale, Material &material) = 0;
	virtual void draw(Shapes::Capsule capsule, Math::Vec3 scale, Material &material) = 0;
	virtual void draw(Shapes::Torus torus, Math::Vec3 scale, Material &material) = 0;
	virtual void draw(Shapes::Polyhedron polyhedron, Math::Vec3 scale, Material &material) = 0;

	virtual void draw(Model3D model, Math::Vec3 position, Math::Vec3 rotation, Math::Vec3 scale, Material &material) = 0;

	void setHudMode() {
		m_hudMode = true;
	}

	void clearHudMode() {
		m_hudMode = false;
	}

  protected:
	bool isHudMode() {
		return m_hudMode;
	}

  private:
	bool m_hudMode = false;
};

class IRendererProgrammable {
  public:
	~IRendererProgrammable() = default;

	enum class ShaderType {
		Vertex = 0,
		Fragment
	};

	virtual u32 createShader(const char *hlslSource, ShaderType type) = 0;
	// May throw NotFoundException, InvalidArgumentException
	virtual void deleteShader(u32 shader) = 0;

	virtual u32 createProgram() = 0;
	// May throw NotFoundException, InvalidArgumentException
	virtual void addProgramShader(u32 program, u32 shader) = 0;
	// May throw NotFoundException, InvalidArgumentException
	virtual void removeProgramShader(u32 program, u32 shader) = 0;
	// May throw NotFoundException, InvalidArgumentException
	virtual void deleteProgram(u32 program) = 0;

	// May throw NotFoundException, InvalidArgumentException
	virtual void useProgram(u32 program) = 0;
	virtual void resetProgram() = 0;
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
