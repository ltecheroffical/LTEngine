#ifdef LTENGINE_COMPONENT_OPENGL
#include <cassert>

#include <LTEngine/backends/opengl/graphics/opengl.hpp>
#include <LTEngine/exceptions/exc_invalid_argument.hpp>


using namespace LTEngine;
using namespace LTEngine::Graphics;

OpenGL::OpenGL(Version version) {
    _version = version;
}

OpenGL::Version OpenGL::get_version() const {
    return _version;
}

#endif // LTENGINE_COMPONENT_OPENGL
