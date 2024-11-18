#include <LTEngine/rendering/opengl_renderer.hpp>


using namespace LTEngine;
using namespace LTEngine::Rendering;


const char *vertexShaderSource = "#version 330 core\n"
                                 "layout(location = 0) in vec2 vPosition;\n"
                                 "layout(location = 1) in vec4 vColor;\n"
                                 "layout(location = 2) in vec2 vTexCoord;\n"
                                 "\n"
                                 "out vec4 fragColor;\n"
                                 "out vec2 texCoord;\n"
                                 "\n"
                                 "void main() {\n"
                                 "   gl_Position = vec4(vPosition, 0.0, 1.0);\n"
                                 "   fragColor = vColor;\n"
                                 "   texCoord = vTexCoord;\n"
                                 "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 finalColor;\n"
                                   "\n"
                                   "uniform bool useTexture;\n"
                                   "uniform sampler2D myTexture;\n"
                                   "\n"
                                   "in vec4 fragColor;\n"
                                   "in vec2 texCoord;\n"
                                   "\n"
                                   "void main() {\n"
                                   "   if (useTexture) {\n"
                                   "        finalColor = texture(myTexture, texCoord) * fragColor;\n"
                                   "   } else {"
                                   "        finalColor = fragColor;\n"
                                   "   }\n"
                                   "}\0";


const GLenum ZDepthFunc = GL_ALWAYS; // GL_GEQUAL; // Simulates Z order, higher is closer


OpenGLRenderer::OpenGLRenderer(u32 width, u32 height, std::function<void()> switchContextCallback) {
	m_switchContextCallback = switchContextCallback;
	switchContext();

	glViewport(0, 0, width, height);
	m_width = width;
	m_height = height;

	u32 vertexShader = compileShader(vertexShaderSource, GL_VERTEX_SHADER);
	u32 fragmentShader = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

	m_defaultShaderProgram = glCreateProgram();
	glAttachShader(m_defaultShaderProgram, vertexShader);
	glAttachShader(m_defaultShaderProgram, fragmentShader);
	glLinkProgram(m_defaultShaderProgram);

	i32 success;
	glGetProgramiv(m_defaultShaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(m_defaultShaderProgram, 512, NULL, infoLog);
		throw std::runtime_error(infoLog);
	}

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	Vertex vertices[] = {};
	glBufferData(GL_ARRAY_BUFFER, 0, &vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, x));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, r));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, u));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(ZDepthFunc);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	resetShader();
}

OpenGLRenderer::~OpenGLRenderer() {
	glDeleteProgram(m_defaultShaderProgram);

	// We don't want an invalid pointer when the debug message callback is called
	glDebugMessageCallback(nullptr, nullptr);
	glDisable(GL_DEBUG_OUTPUT);
}


void OpenGLRenderer::loadOpenGL(GLADloadproc loadProc) {
	if (!gladLoadGLLoader(loadProc)) { throw std::runtime_error("Failed to initialize OpenGL!"); }
}


void OpenGLRenderer::resize(u32 width, u32 height) {
	switchContext();
	glViewport(0, 0, width, height);
	m_width = width;
	m_height = height;
}


void OpenGLRenderer::clear(Color color) {
	RenderQueueOp op;

	op.opType = RenderQueueOp::RenderOpType::Clear;
	op.color = ColorA(color.r, color.g, color.b, 255);

	m_renderOpQueue.push(op);
}

void OpenGLRenderer::clear(ColorA color) {
	RenderQueueOp op;

	op.opType = RenderQueueOp::RenderOpType::ClearA;
	op.color = color;

	m_renderOpQueue.push(op);
}


void OpenGLRenderer::setPixel(Math::Vec2i position, Color color) {
	setPixel(position, color);
}

void OpenGLRenderer::setPixel(Math::Vec2i position, ColorA color) {
	RenderQueueOp op;

	op.opType = RenderQueueOp::RenderOpType::SetPixel;

	op.zOrder = getZOrder();

	op.color = color;
	op.dataPosition = position;

	m_renderOpQueue.push(op);
}

Color OpenGLRenderer::getPixel(Math::Vec2i position) {
	switchContext();
	Color color;
	glReadPixels(position.x, position.y, 1, 1, GL_RGB, GL_FLOAT, &color);
	return color;
}


void OpenGLRenderer::drawRect(Shapes::Rect rect, ColorA color, RendererFlags flags) {
	RenderQueueOp op;

	op.opType = RenderQueueOp::RenderOpType::Rect;

	op.zOrder = getZOrder();
	op.flags = flags;

	op.color = color;

	worldToScreenPosition(&rect.x, &rect.y);
	worldToScreenRotation(&rect.rotation);
	op.dataRect = Shapes::Recti(rect.x, rect.y, rect.w, rect.h);
	op.dataRect.rotation = rect.rotation;

	m_renderOpQueue.push(op);
}

void OpenGLRenderer::drawCircle(Shapes::Circle circle, ColorA color, RendererFlags flags) {
	RenderQueueOp op;

	op.opType = RenderQueueOp::RenderOpType::Circle;

	op.zOrder = getZOrder();
	op.flags = flags;

	op.color = color;

	worldToScreenPosition(&circle.x, &circle.y);
	worldToScreenRotation(&circle.rotation);
	op.dataCircle = circle;
	op.dataCircle.rotation = circle.rotation;

	m_renderOpQueue.push(op);
}


void OpenGLRenderer::drawLine(Math::Vec2 a, Math::Vec2 b, u16 thickness, ColorA color, RendererFlags flags) {
	RenderQueueOp op;

	op.opType = RenderQueueOp::RenderOpType::Line;

	op.zOrder = getZOrder();
	op.flags = flags;

	op.color = color;

	op.dataPointA = worldToScreenPosition(a);
	op.dataPointB = worldToScreenPosition(b);

	m_renderOpQueue.push(op);
}

void OpenGLRenderer::drawPoints(Shapes::Polygon polygon, ColorA color, RendererFlags flags) {
	RenderQueueOp op;

	op.opType = RenderQueueOp::RenderOpType::Polygon;

	op.zOrder = getZOrder();
	op.flags = flags;

	op.color = color;

	op.dataPolygon = polygon;
	for (Math::Vec2 &point : op.dataPolygon.points) { point = worldToScreenPosition(point); }
}


void OpenGLRenderer::drawImage(const Image *image, Math::Vec2i position, f32 rotation, Shapes::Recti region, ColorA color,
                               RendererFlags flags) {
	RenderQueueOp op;

	op.opType = RenderQueueOp::RenderOpType::Image;

	op.zOrder = getZOrder();
	op.flags = flags;

	op.color = color;

	op.dataPosition = worldToScreenPosition(position);
	op.dataRotation = worldToScreenRotation(rotation);
	op.dataRegion = region;

	op.dataImage = image;
}


void OpenGLRenderer::flush() {
	if (m_renderOpQueue.empty()) { return; }

	switchContext();

	while (!m_renderOpQueue.empty()) {
		RenderQueueOp op = m_renderOpQueue.front();
		m_renderOpQueue.pop();

		switch (op.opType) {
			case RenderQueueOp::RenderOpType::SetPixel:
				{
					Vertex vertices[] = {
					    {(f32)op.dataPosition.x, (f32)op.dataPosition.y, op.color.r / 255.f, op.color.g / 255.f, op.color.b / 255.f,
					     op.color.a / 255.f},
					};

					glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

					glDepthFunc(GL_ALWAYS);

					glUseProgram(m_currentShaderProgram);
					glUniform1i(glGetUniformLocation(m_currentShaderProgram, "useTexture"), 0);

					glBindVertexArray(m_vao);
					glDrawArrays(GL_POINTS, 0, 1);
					glDepthFunc(ZDepthFunc);
					break;
				}

			case RenderQueueOp::RenderOpType::Clear:
				glClearColor(op.color.r / 255.f, op.color.g / 255.f, op.color.b / 255.f, 1.f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				break;
			case RenderQueueOp::RenderOpType::ClearA:
				glClearColor(op.color.r / 255.f, op.color.g / 255.f, op.color.b / 255.f, op.color.a / 255.f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				break;

			case RenderQueueOp::RenderOpType::Rect:
				{
					Vertex vertices[] = {
					    // Triangle 1
					    {posToOpenGLX(op.dataRect.x), (f32)posToOpenGLY(op.dataRect.y), op.color.r / 255.f, op.color.g / 255.f,
					     op.color.b / 255.f, op.color.a / 255.f},
					    {posToOpenGLX(op.dataRect.x + op.dataRect.w), posToOpenGLY(op.dataRect.y), op.color.r / 255.f,
					     op.color.g / 255.f, op.color.b / 255.f, op.color.a / 255.f},
					    {posToOpenGLX(op.dataRect.x + op.dataRect.w), posToOpenGLY(op.dataRect.y + op.dataRect.h),
					     op.color.r / 255.f, op.color.g / 255.f, op.color.b / 255.f, op.color.a / 255.f},

					    // Triangle 2
					    {posToOpenGLX(op.dataRect.x), posToOpenGLY(op.dataRect.y), op.color.r / 255.f, op.color.g / 255.f,
					     op.color.b / 255.f, op.color.a / 255.f},
					    {posToOpenGLX(op.dataRect.x), posToOpenGLY(op.dataRect.y + op.dataRect.h), op.color.r / 255.f,
					     op.color.g / 255.f, op.color.b / 255.f, op.color.a / 255.f},
					    {posToOpenGLX(op.dataRect.x + op.dataRect.w), posToOpenGLY(op.dataRect.y + op.dataRect.h),
					     op.color.r / 255.f, op.color.g / 255.f, op.color.b / 255.f, op.color.a / 255.f},
					};

					glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

					glUseProgram(m_currentShaderProgram);
					glUniform1i(glGetUniformLocation(m_currentShaderProgram, "useTexture"), 0);

					glBindVertexArray(m_vao);
					glDrawArrays(GL_TRIANGLES, 0, 6);
					break;
				}
			case RenderQueueOp::RenderOpType::Circle:
				{
					std::vector<Vertex> vertices;

					const u32 TRIANGLE_COUNT = 70;
					for (u32 i = 0; i < TRIANGLE_COUNT; i++) {
						f32 theta = (f32)i / (f32)TRIANGLE_COUNT * 2 * M_PI;
						f32 x = (f32)cos(theta) * op.dataCircle.radius;
						f32 y = (f32)sin(theta) * op.dataCircle.radius;
						vertices.push_back({(f32)op.dataCircle.x + x, (f32)op.dataCircle.y + y, op.color.r / 255.f,
						                    op.color.g / 255.f, op.color.b / 255.f, op.color.a / 255.f});
					}

					glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);

					glUseProgram(m_currentShaderProgram);
					glUniform1i(glGetUniformLocation(m_currentShaderProgram, "useTexture"), 0);

					glBindVertexArray(m_vao);
					glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size());
					break;
				}
			case RenderQueueOp::RenderOpType::Line:
				{
					Vertex vertices[] = {
					    {(f32)op.dataPointA.x, (f32)op.dataPointA.y, op.color.r / 255.f, op.color.g / 255.f, op.color.b / 255.f,
					     op.color.a / 255.f},
					    {(f32)op.dataPointB.x, (f32)op.dataPointB.y, op.color.r / 255.f, op.color.g / 255.f, op.color.b / 255.f,
					     op.color.a / 255.f},
					};

					glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

					glUseProgram(m_currentShaderProgram);
					glUniform1i(glGetUniformLocation(m_currentShaderProgram, "useTexture"), 0);

					glBindVertexArray(m_vao);
					glDrawArrays(GL_LINES, 0, 2);
					break;
				}
			case RenderQueueOp::RenderOpType::Polygon:
				{
					// This gotta be the easiest to draw in OpenGL
					// The hardest part is making the data the correct into vertexes
					std::vector<Vertex> vertices(op.dataPolygon.points.size());

					for (u32 i = 0; i < op.dataPolygon.points.size(); i++) {
						vertices[i] = {(f32)op.dataPolygon.points[i].x,
						               (f32)op.dataPolygon.points[i].y,
						               op.color.r / 255.f,
						               op.color.g / 255.f,
						               op.color.b / 255.f,
						               op.color.a / 255.f};
					}

					glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);

					glUseProgram(m_currentShaderProgram);
					glUniform1i(glGetUniformLocation(m_currentShaderProgram, "useTexture"), 0);

					glBindVertexArray(m_vao);
					glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size());
					break;
				}

			case RenderQueueOp::RenderOpType::Image:
				{
					// This is quite hard to draw (The image is CPU based)
					// Idea: Create a OpenGL texture from the image

					u32 texture = 0;
					if (!m_imageCache.contains(op.dataImage)) {
						glGenTextures(1, &texture);
						glBindTexture(GL_TEXTURE_2D, texture);

						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, op.dataImageNearestFilter ? GL_NEAREST : GL_LINEAR);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, op.dataImageNearestFilter ? GL_NEAREST : GL_LINEAR);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

						glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, op.dataImage->getSize().x, op.dataImage->getSize().y, 0, GL_RGBA,
						             GL_UNSIGNED_BYTE, op.dataImage->getMemBuffer());
						glGenerateMipmap(GL_TEXTURE_2D);

						m_imageCache[op.dataImage] = texture;
						m_imageCacheLifetime[op.dataImage] = MAX_IMAGE_LIFETIME;
					} else {
						texture = m_imageCache[op.dataImage];
						m_imageCacheLifetime[op.dataImage] = MAX_IMAGE_LIFETIME;
					}

					std::erase_if(m_imageCacheLifetime, [this](std::pair<const Image *, u32> pair) {
						if (--pair.second > 0) { return false; }
						glDeleteTextures(1, &m_imageCache[pair.first]);
						const auto it = m_imageCache.find(pair.first);
						if (it != m_imageCache.end()) { m_imageCache.erase(it); }
						return true;
					});

					Vertex vertices[] = {
					    // Triangle 1
					    {posToOpenGLX(op.dataPosition.x), posToOpenGLY(op.dataPosition.y), op.color.r / 255.f, op.color.g / 255.f},
					    {posToOpenGLX(op.dataPosition.x + op.dataRegion.w), posToOpenGLY(op.dataPosition.y), op.color.r / 255.f,
					     op.color.g / 255.f},
					    {posToOpenGLX(op.dataPosition.x + op.dataRegion.w), posToOpenGLY(op.dataPosition.y + op.dataRegion.h),
					     op.color.r / 255.f, op.color.g / 255.f},

					    // Triangle 2
					    {posToOpenGLX(op.dataPosition.x), posToOpenGLY(op.dataPosition.y), op.color.r / 255.f, op.color.g / 255.f},
					    {posToOpenGLX(op.dataPosition.x + op.dataRegion.w), posToOpenGLY(op.dataPosition.y + op.dataRegion.h),
					     op.color.r / 255.f, op.color.g / 255.f},
					    {posToOpenGLX(op.dataPosition.x), posToOpenGLY(op.dataPosition.y + op.dataRegion.h), op.color.r / 255.f,
					     op.color.g / 255.f},
					};

					glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
					glBindTexture(GL_TEXTURE_2D, texture);

					glUseProgram(m_currentShaderProgram);
					glUniform1i(glGetUniformLocation(m_defaultShaderProgram, "useTexture"), 1);

					glBindVertexArray(m_vao);
					glDrawArrays(GL_TRIANGLES, 0, 6);
				}

			default:
				break;
		}
	}
}


u32 OpenGLRenderer::compileShader(const char *source, GLenum type) {
	u32 shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
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

void OpenGLRenderer::deleteShader(u32 shader) {
	glDeleteShader(shader);
}

void OpenGLRenderer::useShader(u32 vertexShader, u32 fragmentShader) {
	if (m_currentShaderProgram != m_defaultShaderProgram) { glDeleteProgram(m_currentShaderProgram); }

	m_currentShaderProgram = glCreateProgram();
	glAttachShader(m_currentShaderProgram, vertexShader);
	glAttachShader(m_currentShaderProgram, fragmentShader);
	glLinkProgram(m_currentShaderProgram);
}

void OpenGLRenderer::resetShader() {
	if (m_currentShaderProgram != m_defaultShaderProgram) { glDeleteProgram(m_currentShaderProgram); }
	m_currentShaderProgram = m_defaultShaderProgram;
}


bool OpenGLRenderer::getMessage(OpenGLMessage *message) {
	if (m_messageQueue.empty()) { return false; }
	*message = m_messageQueue.front();
	m_messageQueue.pop();
	return true;
}


void OpenGLRenderer::switchContext() {
	if (m_switchContextCallback == nullptr) { throw std::runtime_error("Switch context callback not set"); }
	m_switchContextCallback();
}
