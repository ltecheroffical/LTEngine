#ifdef LTENGINE_COMPONENT_RENDERER_LLGL
#include <LLGL/Platform/NativeHandle.h>

#include <LTEngine/rendering/llgl_renderer.hpp>


using namespace LTEngine;
using namespace LTEngine::Rendering;


class LLGLSurface : public LLGL::Surface {
public:
    LLGLSurface(LTEngine::Window *window) {
        m_window = window;
    }
    ~LLGLSurface() = default;


    bool GetNativeHandle(void* nativeHandle, std::size_t nativeHandleSize) override {
        if (nativeHandle != nullptr) {
            auto *handle = static_cast<LLGL::NativeHandle*>(nativeHandle);
            handle->window = *(i32*)m_window->getNativeWindowHandle();
        }
        return false;
    }

    LLGL::Extent2D GetContentSize() const override;
    
    bool AdaptForVideoMode(LLGL::Extent2D *resolution, bool* fullscreen) override;
    
    void ResetPixelFormat() override;

    LLGL::Display * FindResidentDisplay() const override;

private:
    LTEngine::Window *m_window;
};


LLGLRenderer::LLGLRenderer(Window *window, GraphicsAPI api) {
    LLGL::RenderSystemDescriptor rendererDesc;
    {
        const char *rendererBackendLUT[] = {
            "OpenGL",
            "Vulkan",
            "Direct3D11",
            "Direct3D12"
        };
        m_renderer = LLGL::RenderSystem::Load(rendererBackendLUT[(u32)api]);
    }

    LLGL::SwapChainDescriptor swapChainDesc;
    {
        swapChainDesc.resolution = {1, 1};
        m_swapChain = m_renderer->CreateSwapChain(swapChainDesc);
    }

}
#endif