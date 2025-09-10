#if !_LTENGINE_OPENGL_CTX_HPP_ && LTENGINE_COMPONENT_OPENGL
#define _LTEngine_OPENGL_CTX_HPP_

#include <LTEngine/common/compiler_utils.h>

namespace LTEngine::Graphics {
class LTENGINE_API OpenGL {
public:
    enum class Version {
        Version_Invalid = 0,
        Version_3_3 = 0x33,
        Version_1_1 = 0x11,
    };

    // May throw NotPossibleException
    OpenGL(Version version);
    virtual ~OpenGL() = default;
    
    Version get_version() const;

    // Switches the current context to this context
    virtual void make_current() = 0;

private:
    Version _version;
};


class OpenGLOffscreen : public OpenGL {
public:
    OpenGLOffscreen(OpenGL::Version version);
    ~OpenGLOffscreen();
    
    void make_current() override;
};
} // namespace LTEngine::Graphics

#endif // _LTEngine_OPENGL_CTX_HPP_
