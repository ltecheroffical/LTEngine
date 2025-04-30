#ifdef LTENGINE_COMPONENT_RENDERER_OPENGL

#include <battery/embed.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <LTEngine/hash.hpp>

#include <LTEngine/rendering/opengl_renderer.hpp>

using namespace LTEngine;
using namespace LTEngine::Rendering;

const GLenum ZDepthFunc = GL_GEQUAL; // Simulates Z order, higher is closer

OpenGLRenderer::OpenGLRenderer(u32 width, u32 height, std::function<void()> switchContextCallback, Logger *logger) {
	m_switchContextCallback = switchContextCallback;
	switchContext();

	m_logger = logger;

	int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
		glDebugMessageCallback([](
			GLenum source, 
			GLenum type, 
			unsigned int id, 
			GLenum severity, 
			GLsizei length, 
			const char *message, 
			const void *userParam) {
			Logger *logger = (Logger*)(*(Logger**)userParam);

			if ((Logger**)userParam == nullptr) {
				return;
			}

			if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

			logger->error("OPENGL MESSAGE");
			logger->error("Message: %s", message);

			switch (source) {
				case GL_DEBUG_SOURCE_API:            logger->error("Source: API"); break;
				case GL_DEBUG_SOURCE_WINDOW_SYSTEM:  logger->error("Source: Window System"); break;
				case GL_DEBUG_SOURCE_SHADER_COMPILER:logger->error("Source: Shader Compiler"); break;
				case GL_DEBUG_SOURCE_THIRD_PARTY:    logger->error("Source: Third Party"); break;
				case GL_DEBUG_SOURCE_APPLICATION:    logger->error("Source: Application"); break;
				case GL_DEBUG_SOURCE_OTHER:          logger->error("Source: Other"); break;
			} logger->error("");
		
			switch (type) {
				case GL_DEBUG_TYPE_ERROR:              logger->error("Type: Error"); break;
				case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:logger->error("Type: Deprecated Behaviour"); break;
				case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: logger->error("Type: Undefined Behaviour"); break; 
				case GL_DEBUG_TYPE_PORTABILITY:        logger->error("Type: Portability"); break;
				case GL_DEBUG_TYPE_PERFORMANCE:        logger->error("Type: Performance"); break;
				case GL_DEBUG_TYPE_MARKER:             logger->error("Type: Marker"); break;
				case GL_DEBUG_TYPE_PUSH_GROUP:         logger->error("Type: Push Group"); break;
				case GL_DEBUG_TYPE_POP_GROUP:          logger->error("Type: Pop Group"); break;
				case GL_DEBUG_TYPE_OTHER:              logger->error("Type: Other"); break;
			}
			
			switch (severity) {
				case GL_DEBUG_SEVERITY_HIGH:           logger->error("Severity: high"); break;
				case GL_DEBUG_SEVERITY_MEDIUM:         logger->error("Severity: medium"); break;
				case GL_DEBUG_SEVERITY_LOW:            logger->error("Severity: low"); break;
				case GL_DEBUG_SEVERITY_NOTIFICATION:   logger->error("Severity: notification"); break;
			} logger->error("");
		}, &m_logger);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}

	glViewport(0, 0, width, height);
	m_width = width;
	m_height = height;

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(ZDepthFunc);
	glDepthRange(0.f, 1.f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	auto vertexShaderData = b::embed<"resources/opengl/default_shader.vs">().vec();
	auto fragmentShaderData = b::embed<"resources/opengl/default_shader.fs">().vec();
	auto fragmentShaderNormalData = b::embed<"resources/opengl/default_shader_normal.fs">().vec();
	auto fragmentShaderTextureData = b::embed<"resources/opengl/default_shader_texture.fs">().vec();
	auto fragmentShaderCircleData = b::embed<"resources/opengl/default_shader_circle.fs">().vec();

	vertexShaderData.push_back(0x00);
	fragmentShaderData.push_back(0x00);
	fragmentShaderNormalData.push_back(0x00);
	fragmentShaderTextureData.push_back(0x00);
	fragmentShaderCircleData.push_back(0x00);

	u32 vertexShader = compileShader((const char *)vertexShaderData.data(), GL_VERTEX_SHADER);
	u32 fragmentShader = compileShader((const char *)fragmentShaderData.data(), GL_FRAGMENT_SHADER);
	u32 fragmentShaderNormal = compileShader((const char *)fragmentShaderNormalData.data(), GL_FRAGMENT_SHADER);
	u32 fragmentShaderTexture = compileShader((const char *)fragmentShaderTextureData.data(), GL_FRAGMENT_SHADER);
	u32 fragmentShaderCircle = compileShader((const char *)fragmentShaderCircleData.data(), GL_FRAGMENT_SHADER);

	m_defaultShaderProgram = glCreateProgram();
	glAttachShader(m_defaultShaderProgram, vertexShader);
	glAttachShader(m_defaultShaderProgram, fragmentShader);
	glAttachShader(m_defaultShaderProgram, fragmentShaderNormal);
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

	glUseProgram(m_defaultShaderProgram);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, x));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, r));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, u));
	glEnableVertexAttribArray(2);

	resetShader();
}

OpenGLRenderer::~OpenGLRenderer() {
	std::for_each(m_imageCache.begin(), m_imageCache.end(), [](std::pair<const Image *, u32> image) {
		glDeleteTextures(1, &image.second);
	});
	m_imageCache.clear();
	m_imageCacheLifetime.clear();

	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);

	glDeleteProgram(m_defaultShaderProgram);
}

void OpenGLRenderer::resize(u32 width, u32 height) {
	switchContext();
	glViewport(0, 0, width, height);
	m_width = width;
	m_height = height;
}

void OpenGLRenderer::clear(Color color) {
	clear({
		color.r,
		color.g,
		color.b,
		255
	});
}

void OpenGLRenderer::clear(ColorA color) {
	m_renderOpQueue.push({
		.opType = RenderQueueOp::RenderOpType::Clear,
		.payload = {
			.clear = {
				.color = color
			}
		}
	});
}

void OpenGLRenderer::setPixel(Math::Vec2i position, Color color) {
	setPixel(position, {
		color.r,
		color.g,
		color.b,
		255
	});
}

void OpenGLRenderer::setPixel(Math::Vec2i position, ColorA color) {
	m_renderOpQueue.push({
		.opType = RenderQueueOp::RenderOpType::SetPixel,
		.payload = {
			.setPixel = {
				.position = position,
				.color = color
			}
		}
	});
}

void OpenGLRenderer::getPixelPromise(Math::Vec2i position, std::function<void(Color color)> function) {
	m_renderOpQueue.push({
		.opType = RenderQueueOp::RenderOpType::GetPixelPromise,
		.function = function,
		.payload = {
			.getPixelPromise = {
				.position = position,
			}
		}
	});
}

Color OpenGLRenderer::getPixel(Math::Vec2i position) {
	switchContext();
	Color color;
	glReadPixels(position.x, position.y, 1, 1, GL_RGB, GL_FLOAT, &color);
	return color;
}

void OpenGLRenderer::drawRect(Shapes::Rect rect, ColorA color, RendererFlags flags) {
	f32 x = rect.x, y = rect.y;
	worldToScreenPosition(&x, &y);
	m_renderOpQueue.push({
		.opType = RenderQueueOp::RenderOpType::Rect,
		.flags = flags,
		.zOrder = getZOrder(),
		.payload = {
			.drawRect = {
				.rect = {
					x, y,
					rect.w * getWorldScale().x,
					rect.h * getWorldScale().y
				},
				.color = color
			}
		}
	});
}

void OpenGLRenderer::drawCircle(Shapes::Circle circle, ColorA color, RendererFlags flags) {
	f32 x = circle.x, y = circle.y;
	worldToScreenPosition(&x, &y);
	m_renderOpQueue.push({
		.opType = RenderQueueOp::RenderOpType::Circle,
		.flags = flags,
		.zOrder = getZOrder(),
		.payload = {
			.drawCircle = {
				.circle = Shapes::Circle{
					Shapes::Shape(x, y),
					circle.radius * ((getWorldScale().x + getWorldScale().y) / 2)
				}
			}
		}
	});
}

void OpenGLRenderer::drawLine(Math::Vec2 a, Math::Vec2 b, u16 thickness, ColorA color, RendererFlags flags) {
	f32 Ax = a.x, Ay = a.y;
	f32 Bx = b.x, By = b.y;
	worldToScreenPosition(&Ax, &Ay);
	worldToScreenPosition(&Bx, &By);
	m_renderOpQueue.push({
		.opType = RenderQueueOp::RenderOpType::Line,
		.flags = flags,
		.zOrder = getZOrder(),
		.payload = {
			.drawLine = {
				.a = {Ax, Ay},
				.b = {Bx, By},
				.thickness = thickness,
				.color = color
			}
		}
	});
}

void OpenGLRenderer::drawPoints(Shapes::Polygon polygon, ColorA color, RendererFlags flags) {
	m_renderOpQueue.push({
		.opType = RenderQueueOp::RenderOpType::Polygon,
		.flags = flags,
		.zOrder = getZOrder(),
		.polygon = [this](Shapes::Polygon polygon) {
					Shapes::Polygon out;
					for (Math::Vec2 position : polygon.points) {
						out.points.push_back(worldToScreenPosition(position * getWorldScale()));
					}
					out.rotation = worldToScreenRotation(polygon.rotation);
					out.x = polygon.x;
					out.y = polygon.y;
					worldToScreenPosition(&out.x, &out.y);
					return out;
				}(polygon),
		.payload = {
			.drawPoints = {	
				.color = color
			}
		}
	});
}

void OpenGLRenderer::drawImage(const Image *image, Math::Vec2i position, f32 rotation, Shapes::Recti region, ColorA color,
                               RendererFlags flags) {
	m_renderOpQueue.push({

	});
}


void OpenGLRenderer::flush() {
	if (m_renderOpQueue.empty()) {
		return;
	}

	switchContext();

	struct VertexData {
		u16 mode = GL_TRIANGLES;
		u32 shader = 0xFFFFFFFF;
		std::function<void()> preDraw = nullptr;
		Vertex vertex;
	};

	auto defaultVertexPreDraw = [this]() {
		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	};

	u16 order = 0;
	VertexData currentVertex = {.preDraw = nullptr, .vertex = {}};
	std::vector<VertexData> vertexes;

	auto drawVertexes = [this, &vertexes, &currentVertex]() {
		glBufferData(GL_ARRAY_BUFFER, vertexes.size(), vertexes.data(), GL_DYNAMIC_DRAW);
		currentVertex.preDraw();
		glUseProgram(currentVertex.shader);
		glDrawArrays(currentVertex.mode, 0, vertexes.size());
		vertexes.clear();
	};

	auto addVertex = [this, drawVertexes, &defaultVertexPreDraw, &currentVertex, &vertexes, &order](VertexData vertex) {
		if (vertex.shader == 0xFFFFFFFF) {
			vertex.shader = m_defaultShaderProgram;
		}

		if (vertex.preDraw == nullptr) {
			vertex.preDraw = defaultVertexPreDraw;
		}

		if (currentVertex.preDraw == nullptr) {
			currentVertex = vertex;
		}

		if (currentVertex.mode != vertex.mode ||\
			LTEngine::Hash::crc32((const u8*)&currentVertex.preDraw, sizeof(currentVertex.preDraw)) != LTEngine::Hash::crc32((const u8*)&vertex.preDraw, sizeof(vertex.preDraw)) ||\
			currentVertex.shader != vertex.shader) {
			drawVertexes();
			currentVertex = vertex;
		}

		auto newVertex = vertex;
		newVertex.vertex.z += order++;
		vertexes.push_back(newVertex);
	};

	while (!m_renderOpQueue.empty()) {
		RenderQueueOp *op = &m_renderOpQueue.front();

		switch (op->opType) {
			case RenderQueueOp::RenderOpType::SetPixel:
				addVertex({
					.mode = GL_POINT,
					.vertex = {(f32)op->payload.setPixel.position.x,
						(f32)op->payload.setPixel.position.y,
						op->payload.setPixel.color.r / 255.f,
						op->payload.setPixel.color.g / 255.f,
						op->payload.setPixel.color.b / 255.f,
						op->payload.setPixel.color.a / 255.f}});
				break;
			case RenderQueueOp::RenderOpType::GetPixelPromise: {
				Color color;
				drawVertexes();
				glReadPixels(op->payload.getPixelPromise.position.x, op->payload.getPixelPromise.position.y, 1, 1, GL_RGB, GL_FLOAT, &color);
				op->function(color);
				break;
			}

			case RenderQueueOp::RenderOpType::Clear:
				glClearColor(op->payload.clear.color.r / 255.f, op->payload.clear.color.g / 255.f, op->payload.clear.color.b / 255.f, op->payload.clear.color.a / 255.f);
				glClearDepth(0.f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				break;

			case RenderQueueOp::RenderOpType::Rect: {
				auto getRectVertex = [this, op](f32 rectX, f32 rectY) {
						auto [x, y] = rotatePosition(
														{rectX, rectY},
														{
															op->payload.drawRect.rect.x + op->payload.drawRect.rect.w / 2.f,
															op->payload.drawRect.rect.y + op->payload.drawRect.rect.h / 2.f
														},
														op->payload.drawRect.rect.rotation);
						return Vertex{
							posToOpenGLX(x),
							posToOpenGLY(y),
							(f32)op->zOrder / std::numeric_limits<u16>().max(),
							op->payload.drawRect.color.r / 255.f, op->payload.drawRect.color.g / 255.f, op->payload.drawRect.color.b / 255.f,
							op->payload.drawRect.color.a / 255.f
						};
					};

					// Triangle 1
					addVertex({
						.mode = GL_TRIANGLES,
						.vertex = getRectVertex(op->payload.drawRect.rect.x, op->payload.drawRect.rect.y)});

					addVertex({
						.mode = GL_TRIANGLES,
						.vertex = getRectVertex(op->payload.drawRect.rect.x + op->payload.drawRect.rect.w, op->payload.drawRect.rect.y)});
						
					addVertex({
						.mode = GL_TRIANGLES,
						.vertex = getRectVertex(op->payload.drawRect.rect.x + op->payload.drawRect.rect.w, op->payload.drawRect.rect.y + op->payload.drawRect.rect.h)});

					// Triangle 2
					addVertex({
						.mode = GL_TRIANGLES,
						.vertex = getRectVertex(op->payload.drawRect.rect.x, op->payload.drawRect.rect.y)});

					addVertex({
						.mode = GL_TRIANGLES,
						.vertex = getRectVertex(op->payload.drawRect.rect.x + op->payload.drawRect.rect.w, op->payload.drawRect.rect.y + op->payload.drawRect.rect.h)});
						
					addVertex({
						.mode = GL_TRIANGLES,
						.vertex = getRectVertex(op->payload.drawRect.rect.x, op->payload.drawRect.rect.y + op->payload.drawRect.rect.h)});
				}
			}
		m_renderOpQueue.pop();
	}
	drawVertexes();

	/*while (!m_renderOpQueue.empty()) {
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
					glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

					glDrawArrays(GL_POINTS, 0, 1);
					glDepthFunc(ZDepthFunc);
					break;
				}

			case RenderQueueOp::RenderOpType::Clear:
				glClearColor(op.color.r / 255.f, op.color.g / 255.f, op.color.b / 255.f, 1.f);
				glClearDepth(0.f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				break;
			case RenderQueueOp::RenderOpType::ClearA:
				glClearColor(op.color.r / 255.f, op.color.g / 255.f, op.color.b / 255.f, op.color.a / 255.f);
				glClearDepth(0.f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				break;

			case RenderQueueOp::RenderOpType::Rect:
				{
					const auto getRectVertex = [this, op](f32 rectX, f32 rectY) {
						auto [x, y] = rotatePosition({rectX, rectY},
						                             {op.dataRect.x + op.dataRect.w / 2.f, op.dataRect.y + op.dataRect.h / 2.f},
						                             op.dataRect.rotation);
						return (Vertex){posToOpenGLX(x),    posToOpenGLY(y),    (f32)op.zOrder / std::numeric_limits<u16>().max(),
						                op.color.r / 255.f, op.color.g / 255.f, op.color.b / 255.f,
						                op.color.a / 255.f};
					};

					Vertex vertices[6] = {
					    // Triangle 1
					    getRectVertex(op.dataRect.x, op.dataRect.y),
					    getRectVertex(op.dataRect.x + op.dataRect.w, op.dataRect.y),
					    getRectVertex(op.dataRect.x + op.dataRect.w, op.dataRect.y + op.dataRect.h),

					    // Triangle 2
					    getRectVertex(op.dataRect.x, op.dataRect.y),
					    getRectVertex(op.dataRect.x + op.dataRect.w, op.dataRect.y + op.dataRect.h),
					    getRectVertex(op.dataRect.x, op.dataRect.y + op.dataRect.h),
					};

					glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

					glUseProgram(m_currentShaderProgram);
					glUniform1i(glGetUniformLocation(m_currentShaderProgram, "useTexture"), 0);

					glBindVertexArray(m_vao);
					glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

					glDrawArrays(GL_TRIANGLES, 0, 6);
					break;
				}
			case RenderQueueOp::RenderOpType::Circle:
				{
					const u32 TRIANGLE_COUNT = op.dataCircle.radius * 5;
					Vertex vertices[TRIANGLE_COUNT];

					for (u32 i = 0; i < TRIANGLE_COUNT; i++) {
						f32 theta = (f32)i / (f32)TRIANGLE_COUNT * 2 * M_PI;
						f32 x = (f32)cos(theta) * op.dataCircle.radius;
						f32 y = (f32)sin(theta) * op.dataCircle.radius;
						vertices[i] = {posToOpenGLX((f32)op.dataCircle.x + x * op.dataScale.x),
						               posToOpenGLY((f32)op.dataCircle.y + y * op.dataScale.y),
						               (f32)op.zOrder / std::numeric_limits<u16>().max(),
						               op.color.r / 255.f,
						               op.color.g / 255.f,
						               op.color.b / 255.f,
						               op.color.a / 255.f};
					}

					glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * TRIANGLE_COUNT, vertices, GL_DYNAMIC_DRAW);

					glUseProgram(m_currentShaderProgram);
					glUniform1i(glGetUniformLocation(m_currentShaderProgram, "useTexture"), 0);

					glBindVertexArray(m_vao);
					glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

					glDrawArrays(GL_TRIANGLE_FAN, 0, TRIANGLE_COUNT);
					break;
				}
			case RenderQueueOp::RenderOpType::Line:
				{
					auto [xA, yA] = rotatePosition({(f32)op.dataPointA.x, (f32)op.dataPointA.y}, op.dataPointA, op.dataRotation);
					auto [xB, yB] = rotatePosition({(f32)op.dataPointB.x, (f32)op.dataPointB.y}, op.dataPointA, op.dataRotation);

					if (op.flags & FLAG_FLIP_H || op.flags & FLAG_FLIP_V) {
						std::swap(xA, xB);
						std::swap(yA, yB);
					}

					Vertex vertices[2] = {
					    {posToOpenGLX(xA), posToOpenGLY(yA), (f32)op.zOrder / std::numeric_limits<u16>().max(), op.color.r / 255.f,
					     op.color.g / 255.f, op.color.b / 255.f, op.color.a / 255.f},
					    {posToOpenGLX(xB), posToOpenGLY(yB), (f32)op.zOrder / std::numeric_limits<u16>().max(), op.color.r / 255.f,
					     op.color.g / 255.f, op.color.b / 255.f, op.color.a / 255.f},
					};

					glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

					glUseProgram(m_currentShaderProgram);
					glUniform1i(glGetUniformLocation(m_currentShaderProgram, "useTexture"), 0);

					glBindVertexArray(m_vao);
					glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

					glDrawArrays(GL_LINES, 0, 2);
					break;
				}
			case RenderQueueOp::RenderOpType::Polygon:
				{
					if (op.dataPolygon.points.empty()) {
						break;
					}

					// This gotta be the easiest to draw in OpenGL
					// The hardest part is making the data into vertexes
					Vertex vertices[op.dataPolygon.points.size()];

					for (u32 i = 0; i < op.dataPolygon.points.size(); i++) {
						auto [x, y] = rotatePosition({(f32)op.dataPolygon.points[i].x, (f32)op.dataPolygon.points[i].y},
						                             op.dataPolygon.points[0], op.dataRotation);
						vertices[i] = {x,
						               y,
						               (f32)op.zOrder / std::numeric_limits<u16>().max(),
						               op.color.r / 255.f,
						               op.color.g / 255.f,
						               op.color.b / 255.f,
						               op.color.a / 255.f};
					}

					glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * op.dataPolygon.points.size(), vertices, GL_DYNAMIC_DRAW);

					glUseProgram(m_currentShaderProgram);
					glUniform1i(glGetUniformLocation(m_currentShaderProgram, "useTexture"), 0);

					glBindVertexArray(m_vao);
					glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

					glDrawArrays(GL_TRIANGLE_FAN, 0, op.dataPolygon.points.size());
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
						if (--pair.second > 0) {
							return false;
						}
						glDeleteTextures(1, &m_imageCache[pair.first]);
						m_imageCache.erase(pair.first);
						return true;
					});

					const auto getImageVertex = [this, op](f32 rectX, f32 rectY, f32 u, f32 v) {
						auto [x, y] = rotatePosition(
						    {rectX, rectY}, {op.dataPosition.x + op.dataRect.w / 2.f, op.dataPosition.y + op.dataRect.h / 2.f},
						    op.dataRotation);
						return (Vertex){posToOpenGLX(x),
						                posToOpenGLY(y),
						                (f32)op.zOrder / std::numeric_limits<u16>().max(),
						                op.color.r / 255.f,
						                op.color.g / 255.f,
						                op.color.b / 255.f,
						                op.color.a / 255.f,
						                u,
						                v};
					};

					f32 atlasWidth = op.dataImage->getSize().x;
					f32 atlasHeight = op.dataImage->getSize().y;

					f32 u1 = op.dataRect.x / atlasWidth;                    // Left edge of the sub-region
					f32 v1 = op.dataRect.y / atlasHeight;                   // Top edge of the sub-region
					f32 u2 = (op.dataRect.x + op.dataRect.w) / atlasWidth;  // Right edge of the sub-region
					f32 v2 = (op.dataRect.y + op.dataRect.h) / atlasHeight; // Bottom edge of the sub-region

					if (op.flags & FLAG_FLIP_H) {
						std::swap(u1, u2);
					}
					if (op.flags & FLAG_FLIP_V) {
						std::swap(v1, v2);
					}

					Vertex vertices[6] = {
					    // Triangle 1
					    getImageVertex(op.dataPosition.x, op.dataPosition.y, u1, v1),
					    getImageVertex(op.dataPosition.x + op.dataRect.w * op.dataScale.x, op.dataPosition.y, u2, v1),
					    getImageVertex(op.dataPosition.x + op.dataRect.w * op.dataScale.x,
					                   op.dataPosition.y + op.dataRect.h * op.dataScale.y, u2, v2),

					    // Triangle 2
					    getImageVertex(op.dataPosition.x, op.dataPosition.y, u1, v1),
					    getImageVertex(op.dataPosition.x + op.dataRect.w * op.dataScale.x,
					                   op.dataPosition.y + op.dataRect.h * op.dataScale.y, u2, v2),
					    getImageVertex(op.dataPosition.x, op.dataPosition.y + op.dataRect.h * op.dataScale.y, u1, v2)};

					glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

					glUseProgram(m_currentShaderProgram);
					glUniform1i(glGetUniformLocation(m_currentShaderProgram, "useTexture"), 1);

					glBindVertexArray(m_vao);
					glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, op.dataImageNearestFilter ? GL_NEAREST : GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, op.dataImageNearestFilter ? GL_NEAREST : GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

					glBindTexture(GL_TEXTURE_2D, texture);
					glDrawArrays(GL_TRIANGLES, 0, 6);
				}

			default:
				break;
		}
	}*/
}

u32 OpenGLRenderer::compileShader(const char *source, GLenum type) {
	u32 shaderHash = Hash::crc32((const u8*)source, strlen(source));
	if (m_shaderCache.contains(shaderHash)) {
		return m_shaderCache.at(shaderHash);
	}

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
	m_shaderCache[shaderHash] = shader;
	return shader;
}

void OpenGLRenderer::useShader(u32 vertexShader, u32 fragmentShader) {
	if (m_currentShaderProgram != m_defaultShaderProgram) {
		glDeleteProgram(m_currentShaderProgram);
	}

	m_currentShaderProgram = glCreateProgram();
	glAttachShader(m_currentShaderProgram, vertexShader);
	glAttachShader(m_currentShaderProgram, fragmentShader);
	glLinkProgram(m_currentShaderProgram);
}

void OpenGLRenderer::resetShader() {
	m_currentShaderProgram = m_defaultShaderProgram;
}

void OpenGLRenderer::switchContext() {
	if (m_switchContextCallback == nullptr) {
		throw std::runtime_error("Switch context callback not set");
	}
	m_switchContextCallback();
}

#endif