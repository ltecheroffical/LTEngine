#include <LTEngine/rendering/opengl_renderer.hpp>


using namespace LTEngine;
using namespace LTEngine::Rendering;


const char *vertexShaderSource = 
    "#version 330 core\n"
    "layout(location = 0) in vec2 position;\n"
    "layout(location = 1) in vec4 color;\n"
    "\n"
    "out vec4 fragColor;\n"
    "\n"
    "void main() {\n"
    "   gl_Position = vec4(position, 0.0, 1.0);\n"
    "   fragColor = color;\n"
    "}\0";

const char *fragmentShaderSource =
    "#version 330 core\n"
    "in vec4 fragColor;\n"
    "out vec4 finalColor;\n"
    "\n"
    "void main() {\n"
    "   finalColor = fragColor;\n"
    "}\0";


OpenGLRenderer::OpenGLRenderer(u32 width, u32 height, std::function<void()> switchContextCallback) {
    m_switchContextCallback = switchContextCallback;
    switchContext();

    glViewport(0, 0, width, height);
    m_width = width;
    m_height = height;

    m_vertexShader = compileShader(vertexShaderSource, GL_VERTEX_SHADER);
    m_fragmentShader = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, m_vertexShader);
    glAttachShader(m_shaderProgram, m_fragmentShader);
    glLinkProgram(m_shaderProgram);

    i32 success;
    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
        throw std::runtime_error(infoLog);
    }

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, 0, m_vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBindVertexArray(0);
}

OpenGLRenderer::~OpenGLRenderer() {
    glDeleteShader(m_vertexShader);
    glDeleteShader(m_fragmentShader);

    glDeleteProgram(m_shaderProgram);
}


void OpenGLRenderer::loadOpenGL(GLADloadproc loadProc) {
    if (!gladLoadGLLoader(loadProc)) {
        throw std::runtime_error("Failed to initialize OpenGL!");
    }
}


void OpenGLRenderer::resize(u32 width, u32 height) {
    switchContext();
    glViewport(0, 0, width, height);
    m_width = width;
    m_height = height;
}


void OpenGLRenderer::clear(Color color) {
    switchContext();
    glClearColor(color.r / 255.f, color.g / 255.f, color.b / 255.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLRenderer::clear(ColorA color) {
    switchContext();
    glClearColor(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
    glClear(GL_COLOR_BUFFER_BIT);
}


void OpenGLRenderer::setPixel(Math::Vec2i position, Color color) {
    setPixel(position, color);
}

void OpenGLRenderer::setPixel(Math::Vec2i position, ColorA color) {
    m_vertices.push_back({
        posToOpenGLX(position.x),
        posToOpenGLY(position.y),
        color.r / 255.f,
        color.g / 255.f,
        color.b / 255.f,
        color.a / 255.f,
    });
}

Color OpenGLRenderer::getPixel(Math::Vec2i position) {
    switchContext();
    Color color;
    glReadPixels(position.x, position.y, 1, 1, GL_RGB, GL_FLOAT, &color);
    return color;
}


void OpenGLRenderer::drawRect(Shapes::Rect rect, ColorA color, RendererFlags flags) {
    rect.x += m_positionOffset.x;
    rect.y += m_positionOffset.y;

    // Triangle 1 (buttom left, bottom right, top right)
    m_vertices.push_back({ posToOpenGLX(rect.x), posToOpenGLY(rect.y), color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f });
    m_vertices.push_back({ posToOpenGLX(rect.x + rect.w), posToOpenGLY(rect.y), color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f });
    m_vertices.push_back({ posToOpenGLX(rect.x + rect.w), posToOpenGLY(rect.y + rect.h), color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f });

    // Triangle 2 (bottom left, top right, top left)
    m_vertices.push_back({ posToOpenGLX(rect.x), posToOpenGLY(rect.y), color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f });
    m_vertices.push_back({ posToOpenGLX(rect.x + rect.w), posToOpenGLY(rect.y + rect.h), color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f });
    m_vertices.push_back({ posToOpenGLX(rect.x), posToOpenGLY(rect.y + rect.h), color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f });
}

void OpenGLRenderer::drawCircle(Shapes::Circle circle, ColorA color, RendererFlags flags) {
    m_vertexRenderPoints[m_vertices.size()] = [this]() {
        return (VertexDrawInfo){ m_shaderProgram };
    };

    const int numSegments = 100;  // Number of segments to approximate a circle
    float angleStep = 2.0f * M_PI / numSegments;

    circle.x += m_positionOffset.x;
    circle.y += m_positionOffset.y;

    // Add the center vertex
    m_vertices.push_back({ posToOpenGLX(circle.x), posToOpenGLY(circle.y),
                           color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f });

    for (int i = 0; i <= numSegments; ++i) {
        float angle = i * angleStep;
        float x = circle.x + circle.radius * cos(angle);
        float y = circle.y + circle.radius * sin(angle);
        m_vertices.push_back({ posToOpenGLX(x), posToOpenGLY(y),
                               color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f });
    }

    m_vertexRenderPoints[m_vertices.size() - 1] = [this]() {
        return (VertexDrawInfo){ m_shaderProgram, GL_TRIANGLE_FAN };
    };
}


void OpenGLRenderer::drawLine(Math::Vec2 a, Math::Vec2 b, u16 thickness, ColorA color, RendererFlags flags) {
    m_vertexRenderPoints[m_vertices.size()] = [this]() {
        return (VertexDrawInfo){ m_shaderProgram };
    };

    a.x += m_positionOffset.x;
    a.y += m_positionOffset.y;
    b.x += m_positionOffset.x;
    b.y += m_positionOffset.y;

    m_vertices.push_back({ posToOpenGLX(a.x), posToOpenGLY(a.y), color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f });
    m_vertices.push_back({ posToOpenGLX(b.x), posToOpenGLY(b.y), color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f });

    m_vertexRenderPoints[m_vertices.size() - 1] = [this, thickness]() {
        glLineWidth(thickness);
        return (VertexDrawInfo){ m_shaderProgram, GL_LINES };
    };

    m_vertexPostRenderCallbacks[m_vertices.size() - 1] = [this]() {
        glLineWidth(1.f);
    };
}

void OpenGLRenderer::drawPoints(Shapes::Polygon polygon, ColorA color, RendererFlags flags) {
    Math::Vec2 *points = polygon.points.data();
    u32 count = polygon.points.size();

    for (u32 i = 0; i < count; i++) {
        m_vertices.push_back({
            posToOpenGLX(points[i].x), posToOpenGLY(points[i].y),
            color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f
        });
    }

    m_vertexRenderPoints[m_vertices.size() - 1] = [this]() {
        glPointSize(1.f);
        return (VertexDrawInfo){ m_shaderProgram, GL_POINTS };
    };
}


void OpenGLRenderer::drawImage(const Image *image, Math::Vec2i position, f32 rotation, Shapes::Recti region, ColorA color, RendererFlags flags) {
    switchContext();
}


void OpenGLRenderer::present() {
    switchContext();

    if (m_vertices.empty()) {
        return;
    }

    std::vector<Vertex> vertices;

    for (u32 i = 0; i < m_vertices.size(); i++) {
        vertices.push_back(m_vertices[i]);
        if (!m_vertexRenderPoints.contains(i)) {
            continue;
        }

        VertexDrawInfo info = m_vertexRenderPoints[i]();

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        i32 posAttrib = glGetAttribLocation(info.shaderProgram, "position");
        glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(posAttrib);

        i32 colorAttrib = glGetAttribLocation(info.shaderProgram, "color");
        glVertexAttribPointer(colorAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(f32)));
        glEnableVertexAttribArray(colorAttrib);

        std::for_each(info.params.begin(), info.params.end(), [&info](std::pair<char*, VertexDrawInfo::ShaderParam> param) {
            i32 paramAttrib = glGetAttribLocation(info.shaderProgram, param.first);
            if (paramAttrib == -1) {
                return;
            }
            glVertexAttribPointer(paramAttrib, param.second.size, param.second.type, GL_FALSE, param.second.data_size, param.second.data);
            glEnableVertexAttribArray(paramAttrib);
        });

        std::for_each(info.uniforms.begin(), info.uniforms.end(), [&info](std::pair<char*, VertexDrawInfo::ShaderUniform> param) {
            i32 uniformLoc = glGetUniformLocation(info.shaderProgram, param.first);
            if (uniformLoc == -1) {
                return;
            }
            f32* uniformData = static_cast<f32*>(param.second.data);
            switch (param.second.type) {
                case GL_FLOAT:
                    glUniform1f(uniformLoc, uniformData[0]);
                    break;
                case GL_FLOAT_VEC2:
                    glUniform2f(uniformLoc, uniformData[0], uniformData[1]);
                    break;
                case GL_FLOAT_VEC3:
                    glUniform3f(uniformLoc, uniformData[0], uniformData[1], uniformData[2]);
                    break;
                case GL_FLOAT_VEC4:
                    glUniform4f(uniformLoc, uniformData[0], uniformData[1], uniformData[2], uniformData[3]);
                    break;
                default:
                    break;
            }
        });

        glUseProgram(info.shaderProgram);
        glBindVertexArray(m_vao);
        glDrawArrays(info.mode, 0, vertices.size());

        if (m_vertexPostRenderCallbacks.contains(i)) {
            m_vertexPostRenderCallbacks[i]();
        }

        vertices.clear();
    }

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    i32 posAttrib = glGetAttribLocation(m_shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(posAttrib);

    i32 colorAttrib = glGetAttribLocation(m_shaderProgram, "color");
    glVertexAttribPointer(colorAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(f32)));
    glEnableVertexAttribArray(colorAttrib);

    glUseProgram(m_shaderProgram);
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    m_vertices.clear();
    m_vertexRenderPoints.clear();

    // Garbage collector with no downsides
    m_tempBuffer.clear();
}


void OpenGLRenderer::switchContext() {
    if (!m_switchContextCallback) {
        throw std::runtime_error("To use the OpenGL renderer, you need to provide a context switch callback.");
    }
    m_switchContextCallback();
}


f32 OpenGLRenderer::posToOpenGLX(f32 x) {
    return (x / (f32)m_width) * 2.f - 1.f;
}

f32 OpenGLRenderer::posToOpenGLY(f32 y) {
    return 1.f - (y / (f32)m_height) * 2.f;
}


u32 OpenGLRenderer::compileShader(const char *source, GLenum shaderType) {
    u32 shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    i32 success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        throw std::runtime_error(infoLog);
    }
    return shader;
}


void *OpenGLRenderer::allocateTemp(u32 size) {
    u32 index = m_tempBuffer.size();
    m_tempBuffer.resize(m_tempBuffer.size() + size);
    return m_tempBuffer.data() + index;
}
