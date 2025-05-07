#ifdef LTENGINE_COMPONENT_C_API

#include <vector>

#include <LTEngine/c_api/rendering/cpu_shader.h>

#include <LTEngine/rendering/cpu_shader.hpp>


class CCPUShader : public LTEngine::Rendering::CPUShader {
public:
    using FragFunc = void (*)(LTEngine_CPUShaderIO *);

    CCPUShader(FragFunc fragment);
    ~CCPUShader() = default;

    void fragment(LTEngine::Rendering::CPUShaderIO *io) override {
        std::vector<LTEngine_HColor> convertedScreen;
        std::vector<LTEngine_HColorA> convertedTexture;

        convertedScreen.reserve(io->screenSize.x * io->screenSize.y);
        convertedTexture.reserve(io->textureSize.x * io->textureSize.y);

        for (size_t i = 0; i < io->screenSize.x * io->screenSize.y; i++) {
            auto color = io->screen[i];
            convertedScreen.push_back(LTEngine_Color(color.r, color.g, color.b));
        }

        for (size_t i = 0; i < io->textureSize.x * io->textureSize.y; i++) {
            auto color = io->texture[i];
            convertedTexture.push_back(LTEngine_ColorA(color.r, color.g, color.b, color.a));
        }

        LTEngine_HColor *screen = convertedScreen.data();
        LTEngine_HVec2u screenSize = LTEngine_Vec2u(io->screenSize.x, io->screenSize.y);
  
        LTEngine_HColorA *texture = convertedTexture.data();
        LTEngine_HVec2u textureSize = LTEngine_Vec2u(io->textureSize.x, io->textureSize.y);
        LTEngine_HVec2u texturePos = LTEngine_Vec2u(io->texturePos.x, io->texturePos.y);

        LTEngine_CPUShaderIO cIO = {
            .position = LTEngine_Vec2i(io->position.x, io->position.y),
            .color = LTEngine_ColorA(io->color.r, io->color.g, io->color.b, io->color.a),
            
            .screen = screen,
            .screenSize = screenSize,

            .texture = texture,
            .textureSize = textureSize,
            .texturePos = texturePos,

            .time = io->time
        };

        m_fragment(&cIO);

        io->position = {LTEngine_Vec2i_x(cIO.position), LTEngine_Vec2i_y(cIO.position)};
        io->color = {
            LTEngine_ColorA_r(cIO.color),
            LTEngine_ColorA_g(cIO.color),
            LTEngine_ColorA_b(cIO.color),
            LTEngine_ColorA_a(cIO.color)
        };

        for (LTEngine_HColor color : convertedScreen) {
            LTEngine_Color_free(color);
        }
        LTEngine_Vec2u_free(screenSize);


        for (LTEngine_HColorA color : convertedTexture) {
            LTEngine_ColorA_free(color);
        }
        LTEngine_Vec2u_free(textureSize);
        LTEngine_Vec2u_free(texturePos);
    }

    FragFunc getFragmentFunc() {
        return m_fragment;
    }

private:
    FragFunc m_fragment;
};


LTEngine_HCPUShader LTEngine_CustomCPUShader(void (*fragment)(LTEngine_CPUShaderIO *)) {
    return {{ new CCPUShader(fragment) }};
}

void LTEngine_CustomCPUShader_free(LTEngine_HCPUShader shader) {
    delete (CCPUShader*)shader.handle.ptr;
}


void LTEngine_CPUShader_fragment(LTEngine_HCPUShader shader, LTEngine_CPUShaderIO *io) {
    ((CCPUShader*)shader.handle.ptr)->getFragmentFunc()(io);
}

#endif