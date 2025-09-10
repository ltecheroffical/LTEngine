#if !_LTENGINE_OPENGL11_RENDERER_HPP_ && LTENGINE_COMPONENT_OPENGL
#define _LTENGINE_OPENGL11_RENDERER_HPP_

#include <functional>
#include <queue>

#include <glad/glad.h>

#include <LTEngine/graphics/3d/renderer.hpp>
#include <LTEngine/backends/opengl/graphics/opengl.hpp>

namespace LTEngine::Graphics {
class LTENGINE_API OpenGL11Renderer3D : public Renderer {
public:
    OpenGL11Renderer3D(OpenGL *context);
    ~OpenGL11Renderer3D();

    void clear(ColorA color) override;

    void set_pixel(ColorA pixel, Math::Vec2 position) override;

	void draw(Shapes::Cube cube, Math::Vec3 scale, Material &material) override;
	void draw(Shapes::Sphere sphere, Math::Vec3 scale, Material &material) override;
	void draw(Shapes::Cylinder cylinder, Math::Vec3 scale, Material &material) override;
	void draw(Shapes::Capsule capsule, Math::Vec3 scale, Material &material) override;
	void draw(Shapes::Torus torus, Math::Vec3 scale, Material &material) override;
	void draw(Shapes::Polyhedron polyhedron, Math::Vec3 scale, Material &material) override;

	void draw(Model3D model, Math::Vec3 position, Math::Vec3 rotation, Math::Vec3 scale, Material &material) override;

    // I hate too many ctx switches
    void flush();

private:
    typedef std::function<void()> DrawCmdFunction;

    struct DrawCmd {
        DrawCmdFunction cmd;
        GLint type;
    };

    OpenGL *_context;
    std::queue<DrawCmd> _draw_cmds;

    // If type is -1, it will not be run inside verrtices
    void _add_draw_cmd(DrawCmdFunction function, GLint type);

    Math::Vec2 _to_ndc2d(Math::Vec2 position);
    Math::Vec2 _from_ndc2d(Math::Vec2 ndc);
};
} // namespace LTEngine::Graphics

#endif // _LTENGINE_OPENGL11_RENDERER_HPP_
