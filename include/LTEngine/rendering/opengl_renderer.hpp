#pragma once

#include <vector>
#include <functional>
#include <unordered_map>

#include <glad/glad.h>

#include <LTEngine/rendering/renderer.hpp>


namespace LTEngine::Rendering {
    class OpenGLRenderer : public Renderer {
    public:
        OpenGLRenderer(u32 width, u32 height, std::function<void()> switchContextCallback);
        ~OpenGLRenderer() override;

        static void loadOpenGL(GLADloadproc loadProc);

        void resize(u32 width, u32 height);

        void clear(Color color) override;
        void clear(ColorA color) override;

        void setPixel(Math::Vec2i position, Color color) override;
        void setPixel(Math::Vec2i position, ColorA color) override;
        Color getPixel(Math::Vec2i position) override;

        void drawRect(Shapes::Rect rect, ColorA color, RendererFlags flags) override;
        void drawCircle(Shapes::Circle circle, ColorA color, RendererFlags flags) override;

        void drawLine(Math::Vec2 a, Math::Vec2 b, u16 thickness, ColorA color, RendererFlags flags) override;
        void drawPoints(Shapes::Polygon polygon, ColorA color, RendererFlags flags) override;

        void drawImage(const Image *image, Math::Vec2i position, f32 rotation, Shapes::Recti region, ColorA color, RendererFlags flags) override;

        void present();

    private:
        void switchContext();

        f32 posToOpenGLX(f32 x);
        f32 posToOpenGLY(f32 y);

        struct Vertex {
            f32 x, y;
            f32 r, g, b, a;
        };

        struct VertexDrawInfo {
            struct ShaderParam {
                i32 size;
                GLenum type;
                void *data;
                u32 data_size;
            };

            struct ShaderUniform {
                GLenum type;
                void *data;
            };
            
            u32 shaderProgram;
            GLenum mode = GL_TRIANGLES;
            std::unordered_map<char*, ShaderParam> params = {};
            std::unordered_map<char*, ShaderUniform> uniforms = {};
        };

        u32 compileShader(const char *source, GLenum shaderType);

        void *allocateTemp(u32 size);

        std::function<void()> m_switchContextCallback = nullptr;

        std::unordered_map<u32, std::function<VertexDrawInfo()>> m_vertexRenderPoints;
        std::unordered_map<u32, std::function<void()>> m_vertexPostRenderCallbacks;

        std::vector<Vertex> m_vertices;

        std::vector<char> m_tempBuffer;

        u32 m_width;
        u32 m_height;

        u32 m_vbo;
        u32 m_vao;

        i32 m_posAttrib;
        i32 m_colorAttrib;

        u32 m_shaderProgram;

        u32 m_vertexShader;
        u32 m_fragmentShader;
    };
}
