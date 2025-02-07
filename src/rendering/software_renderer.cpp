#include <cmath>

#include <LTEngine/rendering/software_renderer.hpp>


using namespace LTEngine;
using namespace LTEngine::Rendering;


#define UNALLOCATED_COLOR ColorA(0x3A, 0x6B, 0x2F, 0xFF)


SoftwareRenderer::SoftwareRenderer(u32 width, u32 height) : m_screenWidth(width), m_screenHeight(height) {
	m_screen.resize(m_screenWidth * m_screenHeight, Color::Black);
	m_screenDepth.resize(m_screenWidth * m_screenHeight, 0);
	m_screenOnly = false;
}


void SoftwareRenderer::resize(u32 width, u32 height) {
	m_screenWidth = width;
	m_screenHeight = height;
	std::for_each(m_cameraOutputs.begin(), m_cameraOutputs.end(), [width, height](std::pair<u32, std::vector<Color>> output) {
		output.second.resize(width * height, Color::Black);
	});
	std::for_each(m_cameraDepth.begin(), m_cameraDepth.end(), [width, height](std::pair<u32, std::vector<u16>> output) {
		output.second.resize(width * height, 0);
	});
	m_screen.resize(m_screenWidth * m_screenHeight, Color::Black);
	m_screenDepth.resize(m_screenWidth * m_screenHeight, 0);
}


size_t SoftwareRenderer::getScreenData(Color *data) {
	if (data != nullptr) {
		memcpy(data, m_screen.data(), sizeof(Color) * m_screenWidth * m_screenHeight);
	}
	return m_screen.size();
}

void SoftwareRenderer::setScreenOnly() {
	m_screenOnly = true;
}

void SoftwareRenderer::clearScreenOnly() {
	m_screenOnly = false;
}


void SoftwareRenderer::clear(Color color) {
	RendererQueueOp op;
	op.opType = RendererQueueOp::RenderOpType::Clear;
	op.screenOnly = m_screenOnly;
	op.color = ColorA(color.r, color.g, color.b, 255);

	std::shared_lock<std::shared_mutex> lock(m_renderQueueMutex);
	m_rendererQueue.push(op);
}

void SoftwareRenderer::clear(ColorA color) {
	RendererQueueOp op;
	op.opType = RendererQueueOp::RenderOpType::Clear;
	op.screenOnly = m_screenOnly;
	op.color = color;

	std::shared_lock<std::shared_mutex> lock(m_renderQueueMutex);
	m_rendererQueue.push(op);
}


void SoftwareRenderer::setPixel(Math::Vec2i position, Color color) {
	setPixel(position, ColorA(color.r, color.g, color.b, 255));
}

void SoftwareRenderer::setPixel(Math::Vec2i position, ColorA color) {
	RendererQueueOp op;
	op.opType = RendererQueueOp::RenderOpType::SetPixel;
	op.screenOnly = m_screenOnly;
	op.color = color;
	op.dataPosition = position;
	op.shader = m_shader;

	std::shared_lock<std::shared_mutex> lock(m_renderQueueMutex);
	m_rendererQueue.push(op);
}

Color SoftwareRenderer::getPixel(Math::Vec2i position) {
	return m_screen.at(position.y * m_screenWidth + position.x);
}


void SoftwareRenderer::drawRect(Shapes::Rect rect, ColorA color, RendererFlags flags) {
	RendererQueueOp op;
	op.opType = RendererQueueOp::RenderOpType::Rect;
	op.screenOnly = m_screenOnly;
	op.color = color;
	op.zOrder = getZOrder();
	op.flags = flags;
	op.shader = m_shader;

	worldToScreenPosition(&rect.x, &rect.y);
	worldToScreenRotation(&rect.rotation);
	op.dataRect = Shapes::Recti(rect.x, rect.y, rect.w, rect.h);
	op.dataRect.rotation = rect.rotation;
	op.dataScale = getWorldScale();

	std::shared_lock<std::shared_mutex> lock(m_renderQueueMutex);
	m_rendererQueue.push(op);
}

void SoftwareRenderer::drawCircle(Shapes::Circle circle, ColorA color, RendererFlags flags) {
	RendererQueueOp op;
	op.opType = RendererQueueOp::RenderOpType::Circle;
	op.screenOnly = m_screenOnly;
	op.color = color;
	op.zOrder = getZOrder();
	op.flags = flags;
	op.shader = m_shader;

	worldToScreenPosition(&circle.x, &circle.y);
	worldToScreenRotation(&circle.rotation);
	op.dataCircle = circle;

	std::shared_lock<std::shared_mutex> lock(m_renderQueueMutex);
	m_rendererQueue.push(op);
}


void SoftwareRenderer::drawLine(Math::Vec2 a, Math::Vec2 b, u16 thickness, ColorA color, RendererFlags flags) {
	RendererQueueOp op;
	op.opType = RendererQueueOp::RenderOpType::Line;
	op.screenOnly = m_screenOnly;
	op.color = color;
	op.zOrder = getZOrder();
	op.flags = flags;
	op.shader = m_shader;

	op.dataPointA = worldToScreenPosition(a);
	op.dataPointB = worldToScreenPosition(b);
	op.dataThickness = thickness;

	op.dataScale = getWorldScale();

	std::shared_lock<std::shared_mutex> lock(m_renderQueueMutex);
	m_rendererQueue.push(op);
}

void SoftwareRenderer::drawPoints(Shapes::Polygon polygon, ColorA color, RendererFlags flags) {
	RendererQueueOp op;
	op.opType = RendererQueueOp::RenderOpType::Polygon;
	op.screenOnly = m_screenOnly;
	op.color = color;
	op.zOrder = getZOrder();
	op.flags = flags;
	op.shader = m_shader;

	op.dataScale = getWorldScale();

	worldToScreenRotation(&polygon.rotation);
	op.dataPolygon = polygon;
	for (Math::Vec2 &point : op.dataPolygon.points) {
		point = worldToScreenPosition(point);
	}

	std::shared_lock<std::shared_mutex> lock(m_renderQueueMutex);
	m_rendererQueue.push(op);
}


void SoftwareRenderer::drawImage(const Image *image, Math::Vec2i position, f32 rotation, Shapes::Recti region, ColorA color,
                                 RendererFlags flags) {
	RendererQueueOp op;
	op.opType = RendererQueueOp::RenderOpType::Image;
	op.screenOnly = m_screenOnly;
	op.color = color;
	op.zOrder = getZOrder();
	op.flags = flags;
	op.shader = m_shader;

	op.dataPosition = worldToScreenPosition((Math::Vec2i){position.x, position.y});
	op.dataRotation = worldToScreenRotation(rotation);
	op.dataRect = region;
	op.dataScale = getWorldScale();
	op.dataImage = image;

	std::shared_lock<std::shared_mutex> lock(m_renderQueueMutex);
	m_rendererQueue.push(op);
}

void SoftwareRenderer::drawCamera(u32 id, Shapes::Recti rect, ColorA color, RendererFlags flags) {
	RendererQueueOp op;
	op.opType = RendererQueueOp::RenderOpType::Camera;
	op.screenOnly = m_screenOnly;
	op.color = color;
	op.zOrder = getZOrder();
	op.flags = flags;
	op.shader = m_shader;

	worldToScreenPosition(&rect.x, &rect.y);
	op.dataRect = Shapes::Recti(rect.x, rect.y, rect.w, rect.h);
	op.dataCamId = id;

	std::shared_lock<std::shared_mutex> lock(m_renderQueueMutex);
	m_rendererQueue.push(op);
}


bool SoftwareRenderer::process() {
	RendererQueueOp op;
	{
		std::unique_lock lock(m_renderQueueMutex);
		if (m_rendererQueue.empty()) {
			return false;
		}

		op = m_rendererQueue.front();
		m_rendererQueue.pop();
	}

	auto blendColors = [](ColorA color, Color bg) {
		const f32 A_n = color.a / 255.f;
		return Color(color.r * A_n, color.g * A_n, color.b * A_n) + (bg * (1.f - A_n));
	};

	switch (op.opType) {
		case RendererQueueOp::RenderOpType::SetPixel:
			if (op.screenOnly) {
				m_screenMutex.lock();

				const f32 A_n = op.color.a / 255.f;
				const Color bg = m_screen.at(op.dataPosition.y * m_screenWidth + op.dataPosition.x);
				m_screen.at(op.dataPosition.y * m_screenWidth + op.dataPosition.x) = blendColors(op.color, bg);
				m_screenMutex.unlock();
				break;
			}

			std::for_each(m_cameraOutputs.begin(), m_cameraOutputs.end(),
			              [this, blendColors, op](std::pair<u32, std::vector<Color>> output) {
				              Camera *camera = getCameraById(output.first);
				              if (camera == nullptr) {
					              return;
				              }
				              if (camera->exclude) {
					              return;
				              }

				              const f32 A_n = op.color.a / 255.f;
				              const Color bg = output.second.at(op.dataPosition.y * m_screenWidth + op.dataPosition.x);
				              output.second.at(op.dataPosition.y * m_screenWidth + op.dataPosition.x) = blendColors(op.color, bg);
			              });

			break;

		case RendererQueueOp::RenderOpType::Clear:
			if (op.screenOnly) {
				m_screenMutex.lock();
				std::fill(m_screen.begin(), m_screen.end(), op.color);
				std::fill(m_screenDepth.begin(), m_screenDepth.end(), 0);
				m_screenMutex.unlock();
				break;
			}

			std::for_each(m_cameraOutputs.begin(), m_cameraOutputs.end(), [this, op](std::pair<u32, std::vector<Color>> output) {
				Camera *camera = getCameraById(output.first);
				if (camera == nullptr) {
					return;
				}
				if (camera->exclude) {
					return;
				}

				std::fill(output.second.begin(), output.second.end(), op.color);
				std::fill(m_cameraDepth[output.first].begin(), m_cameraDepth[output.first].end(), 0);
			});
			break;
		case RendererQueueOp::RenderOpType::ClearA:
			if (op.screenOnly) {
				m_screenMutex.lock();
				std::transform(m_screen.begin(), m_screen.end(), m_screen.begin(), [op, blendColors](Color color) {
					return blendColors(op.color, color);
				});
				std::fill(m_screenDepth.begin(), m_screenDepth.end(), 0);
				m_screenMutex.unlock();
				break;
			}
			std::for_each(m_cameraOutputs.begin(), m_cameraOutputs.end(),
			              [this, op, blendColors](std::pair<u32, std::vector<Color>> output) {
				              Camera *camera = getCameraById(output.first);
				              if (camera == nullptr) {
					              return;
				              }
				              if (camera->exclude) {
					              return;
				              }

				              std::transform(output.second.begin(), output.second.end(), output.second.begin(),
				                             [op, blendColors](Color color) {
					                             return blendColors(op.color, color);
				                             });
				              std::fill(m_cameraDepth[output.first].begin(), m_cameraDepth[output.first].end(), 0);
			              });
			break;

		case RendererQueueOp::RenderOpType::Rect:
			{
				prepareBuffer(op.dataRect.w, op.dataRect.h);
				for (u32 y = 0; y < op.dataRect.h; y++) {
					for (u32 x = 0; x < op.dataRect.w; x++) { // Why this order? It's about CPU caching!
						drawBufferPixel(x, y, op.color);
					}
				}
				displayBuffer(op.dataRect.x, op.dataRect.y, &op, op.dataRect.rotation % 360);
				break;
			}
		case RendererQueueOp::RenderOpType::Circle:
			{
				u32 radius = op.dataCircle.radius;

				prepareBuffer(2 * radius + 1, 2 * radius + 1);

				u32 centerX = radius;
				u32 centerY = radius;

				i32 x = radius;
				i32 y = 0;
				i32 p = 1 - radius;

				while (x >= y) {
					drawBufferPixel(centerX + x, centerY + y, op.color);
					drawBufferPixel(centerX + x, centerY - y, op.color);
					drawBufferPixel(centerX - x, centerY + y, op.color);
					drawBufferPixel(centerX - x, centerY - y, op.color);
					drawBufferPixel(centerX + y, centerY + x, op.color);
					drawBufferPixel(centerX + y, centerY - x, op.color);
					drawBufferPixel(centerX - y, centerY + x, op.color);
					drawBufferPixel(centerX - y, centerY - x, op.color);

					if (p <= 0) {
						p += 2 * ++y + 1;
					} else {
						p += 2 * (++y - --x) + 1;
					}
				}


				if (op.flags & Renderer::FLAG_FILL) {
					for (u32 y = 0; y < 2 * radius + 1; y++) {
						for (u32 x = 0; x < 2 * radius + 1; x++) {
							// Do not draw outside the circle
							i32 dx = x - radius;
							i32 dy = y - radius;

							if (dx * dx + dy * dy > radius * radius) {
								continue;
							}
							drawBufferPixel(x, y, op.color);
						}
					}
				}


				displayBuffer(op.dataCircle.x - radius - 1, op.dataCircle.y - radius - 1, &op, (i16)op.dataCircle.rotation % 360);
				break;
			}
		case RendererQueueOp::RenderOpType::Line:
			{
				u32 width = abs((i32)op.dataPointB.x - (i32)op.dataPointA.x) + 1;
				u32 height = abs((i32)op.dataPointB.y - (i32)op.dataPointA.y) + 1;

				prepareBuffer(width, height);

				i32 positionX = (op.dataPointA.x < op.dataPointB.x) ? op.dataPointA.x : op.dataPointB.x;
				i32 positionY = (op.dataPointA.y < op.dataPointB.y) ? op.dataPointA.y : op.dataPointB.y;

				op.dataPointA.x -= positionX;
				op.dataPointA.y -= positionY;
				op.dataPointB.x -= positionX;
				op.dataPointB.y -= positionY;

				i32 dx = abs((i32)op.dataPointB.x - (i32)op.dataPointA.x);
				i32 dy = abs((i32)op.dataPointB.y - (i32)op.dataPointA.y);
				i32 sx = (op.dataPointA.x < op.dataPointB.x) ? 1 : -1;
				i32 sy = (op.dataPointA.y < op.dataPointB.y) ? 1 : -1;
				i32 err = dx - dy;

				while (true) {
					for (i32 dx = -op.dataThickness; dx <= op.dataThickness / 2; dx++) {
						for (i32 dy = -op.dataThickness; dy <= op.dataThickness / 2; dy++) {
							if (op.dataPointA.x + dx < 0 || op.dataPointA.x + dx >= width || op.dataPointA.y + dy < 0 ||
							    op.dataPointA.y + dy >= height) {
								continue;
							}
							drawBufferPixel(op.dataPointA.x + dx, op.dataPointA.y + dy, op.color);
						}
					}

					if (op.dataPointA.x == op.dataPointB.x && op.dataPointA.y == op.dataPointB.y) {
						break;
					}

					i32 e2 = 2 * err;
					if (e2 > -dy) {
						err -= dy;
						op.dataPointA.x += sx;
					}
					if (e2 < dx) {
						err += dx;
						op.dataPointA.y += sy;
					}
				}

				displayBuffer(positionX, positionY, &op, 0.f);
				break;
			}

		case RendererQueueOp::RenderOpType::Polygon:
			{
				Math::Vec2 *points = op.dataPolygon.points.data();
				u32 count = op.dataPolygon.points.size();

				for (u32 i = 0; i < count; i++) {
					Math::Vec2 point_a = points[i];
					Math::Vec2 point_b = points[(i + 1) % count];

					drawLine(point_a, point_b, 1, op.color, op.flags);
				}

				if (op.flags & Renderer::FLAG_FILL) {
					i32 min_x = points[0].x, max_x = points[0].x;
					i32 min_y = points[0].y, max_y = points[0].y;

					for (u32 i = 1; i < count; i++) {
						if (points[i].x < min_x)
							min_x = points[i].x;
						if (points[i].x > max_x)
							max_x = points[i].x;
						if (points[i].y < min_y)
							min_y = points[i].y;
						if (points[i].y > max_y)
							max_y = points[i].y;
					}

					u32 bufferWidth = max_x - min_x + 1;
					u32 bufferHeight = max_y - min_y + 1;

					prepareBuffer(bufferWidth, bufferHeight);

					for (i32 y = min_y; y <= max_y; y++) {
						i32 intersections[count];
						u32 num_intersections = 0;

						for (u32 i = 0; i < count; i++) {
							Math::Vec2 point_a = points[i];
							Math::Vec2 point_b = points[(i + 1) % count];

							if ((point_a.y <= y && point_b.y > y) || (point_b.y <= y && point_a.y > y)) {
								i32 x_intersect = point_a.x + (y - point_a.y) * (point_b.x - point_a.x) / (point_b.y - point_a.y);
								intersections[num_intersections++] = x_intersect;
							}
						}

						std::sort(intersections, intersections + num_intersections);

						for (u32 i = 0; i < num_intersections; i += 2) {
							if (i + 1 < num_intersections) {
								for (i32 x = intersections[i]; x <= intersections[i + 1]; x++) {
									drawBufferPixel(x, y, op.color);
								}
							}
						}
					}

					u32 posX = min_x;
					u32 posY = min_y;
					displayBuffer(posX, posY, &op, (i16)op.dataPolygon.rotation % 360);
				}
				break;
			}
		case RendererQueueOp::RenderOpType::Image:
			{
				u32 imageWidth = op.dataRect.w;
				u32 imageHeight = op.dataRect.h;

				prepareBuffer(imageWidth, imageHeight);

				for (u32 y = 0; y < imageHeight; y++) {
					for (u32 x = 0; x < imageWidth; x++) {
						drawBufferPixel(x, y, op.dataImage->getPixel(op.dataRect.x + x, op.dataRect.y + y));
					}
				}

				displayBuffer(op.dataPosition.x, op.dataPosition.y, &op, (i16)op.dataRotation % 360);
				break;
			}
		case RendererQueueOp::RenderOpType::Camera:
			{
				prepareBuffer(op.dataRect.w, op.dataRect.h);

				for (u32 y = 0; y < op.dataRect.h; y++) {
					for (u32 x = 0; x < op.dataRect.w; x++) {
						drawBufferPixel(x, y,
						                ColorA(m_cameraOutputs.at(op.dataCamId).at(y * m_screenWidth + x).r,
						                       m_cameraOutputs.at(op.dataCamId).at(y * m_screenWidth + x).g,
						                       m_cameraOutputs.at(op.dataCamId).at(y * m_screenWidth + x).b, 255));
					}
				}

				displayBuffer(op.dataRect.x, op.dataRect.y, &op, op.dataRect.rotation % 360);
				break;
			}
		default:
			break;
	}

	return true;
}

void SoftwareRenderer::processAll() {
	// Yes, it's dead simple
	while (process())
		;
}


void SoftwareRenderer::setScalingMode(ScalingMode mode) {
	m_scalingMode = mode;
}


void SoftwareRenderer::setShader(CPUShader *shader) {
	m_shader = shader;
}

void SoftwareRenderer::clearShader() {
	m_shader = nullptr;
}


void SoftwareRenderer::prepareBuffer(u32 width, u32 height) {
	size_t bufferSize = width * height;

	if (m_buffer.size() < bufferSize) {
		m_buffer.resize(bufferSize);
	}

	m_bufferWidth = width;
	m_bufferHeight = height;

	std::fill(m_buffer.begin(), m_buffer.end(), ColorA::Clear);
}

void SoftwareRenderer::drawBufferPixel(u32 x, u32 y, ColorA color) {
	size_t index = y * m_bufferWidth + x;
	m_buffer[index] = color;
}

ColorA SoftwareRenderer::getBufferPixel(u32 x, u32 y) {
	size_t index = y * m_bufferWidth + x;
	return m_buffer[index];
}


void SoftwareRenderer::displayBuffer(i32 posX, i32 posY, const RendererQueueOp *op, f32 rotation) {
	if (m_screenOnly && m_cameraSelected) {
		return;
	}

	const auto blendPixel = [this, op, &posX, &posY](ColorA color, Math::Vec2u texturePosition) -> Color {
		Color bg = m_screen[(texturePosition.y + posY) * m_screenWidth + (texturePosition.x + posX)];
		const f32 A_n = color.a / 255.f;

		f32 out_r = color.r * A_n + bg.r * (1.f - A_n);
		f32 out_g = color.g * A_n + bg.g * (1.f - A_n);
		f32 out_b = color.b * A_n + bg.b * (1.f - A_n);

		return Color(out_r, out_g, out_b);
	};

	u32 bufferWidth = m_bufferWidth;
	u32 bufferHeight = m_bufferHeight;

	allocateWorkspace1(bufferWidth, bufferHeight);

	for (u32 y = 0; y < bufferHeight; y++) {
		for (u32 x = 0; x < bufferWidth; x++) {
			ColorA color = getBufferPixel(x, y);
			if (op->shader != nullptr) {
				CPUShaderIO io = {.position = Math::Vec2i(posX, posY),
				                  .color = op->color,

				                  .screen = m_screen.data(),
				                  .screenSize = {m_screenWidth, m_screenHeight},

				                  .texture = m_buffer.data(),
				                  .textureWidth = bufferWidth,
				                  .textureHeight = bufferHeight,
				                  .textureX = x,
				                  .textureY = y,

				                  .time = (op->timestamp.time_since_epoch().count() - m_creationTime.time_since_epoch().count()) /
				                          1000000000.f};

				op->shader->fragment(&io);

				color = io.color;
				posX = io.position.x;
				posY = io.position.y;
			}
			drawWorkspace1Pixel(x, y, color);
		}
	}

	allocateWorkspace2(bufferWidth * op->dataScale.x, bufferHeight * op->dataScale.y);

	switch (m_scalingMode) {
		case ScalingMode::Nearest:
			for (u32 y = 0; y < bufferHeight * op->dataScale.y; y++) {
				for (u32 x = 0; x < bufferWidth * op->dataScale.x; x++) {
					drawWorkspace2Pixel(x, y, getWorkspace1Pixel(x / op->dataScale.x, y / op->dataScale.y));
				}
			}
			break;
		case ScalingMode::Linear:
			// Uh oh... (This requires lots of math)
			for (u32 y = 0; y < bufferHeight * op->dataScale.y; y++) {
				for (u32 x = 0; x < bufferWidth * op->dataScale.x; x++) {
					f32 origX = x / op->dataScale.x;
					f32 origY = y / op->dataScale.y;

					u32 x1 = static_cast<u32>(std::floor(origX));
					u32 y1 = static_cast<u32>(std::floor(origY));
					u32 x2 = std::min(x1 + 1, bufferWidth - 1);
					u32 y2 = std::min(y1 + 1, bufferHeight - 1);

					f32 xLerp = origX - x1;
					f32 yLerp = origY - y1;

					ColorA topLeft = getWorkspace1Pixel(x1, y1);
					ColorA topRight = getWorkspace1Pixel(x2, y1);
					ColorA bottomLeft = getWorkspace1Pixel(x1, y2);
					ColorA bottomRight = getWorkspace1Pixel(x2, y2);

					ColorA topRow = {static_cast<u8>(topLeft.r + xLerp * (topRight.r - topLeft.r)),
					                 static_cast<u8>(topLeft.g + xLerp * (topRight.g - topLeft.g)),
					                 static_cast<u8>(topLeft.b + xLerp * (topRight.b - topLeft.b)),
					                 static_cast<u8>(topLeft.a + xLerp * (topRight.a - topLeft.a))};

					ColorA bottomRow = {static_cast<u8>(bottomLeft.r + xLerp * (bottomRight.r - bottomLeft.r)),
					                    static_cast<u8>(bottomLeft.g + xLerp * (bottomRight.g - bottomLeft.g)),
					                    static_cast<u8>(bottomLeft.b + xLerp * (bottomRight.b - bottomLeft.b)),
					                    static_cast<u8>(bottomLeft.a + xLerp * (bottomRight.a - bottomLeft.a))};

					drawWorkspace2Pixel(x, y,
					                    {static_cast<u8>(topRow.r + yLerp * (bottomRow.r - topRow.r)),
					                     static_cast<u8>(topRow.g + yLerp * (bottomRow.g - topRow.g)),
					                     static_cast<u8>(topRow.b + yLerp * (bottomRow.b - topRow.b)),
					                     static_cast<u8>(topRow.a + yLerp * (bottomRow.a - topRow.a))});
				}
			}
			break;
	}


	f32 scaledWidth = bufferWidth * op->dataScale.x;
	f32 scaledHeight = bufferHeight * op->dataScale.y;
	u32 diagonal = static_cast<u32>(std::ceil(std::sqrt(scaledWidth * scaledWidth + scaledHeight * scaledHeight)));

	allocateWorkspace1(diagonal, diagonal);

	f32 centerX = scaledWidth / 2.0f;
	f32 centerY = scaledHeight / 2.0f;
	f32 offset = diagonal / 2.0f;

	f32 cosTheta = cos(rotation * M_PI / 180.0f);
	f32 sinTheta = sin(rotation * M_PI / 180.0f);

	for (u32 y = 0; y < static_cast<u32>(scaledHeight); y++) {
		for (u32 x = 0; x < static_cast<u32>(scaledWidth); x++) {
			f32 translatedX = x - centerX;
			f32 translatedY = y - centerY;

			i32 rotatedX = static_cast<i32>(translatedX * cosTheta - translatedY * sinTheta + offset);
			i32 rotatedY = static_cast<i32>(translatedX * sinTheta + translatedY * cosTheta + offset);

			if (rotatedX < 0 || rotatedY < 0 || rotatedX >= static_cast<i32>(diagonal) || rotatedY >= static_cast<i32>(diagonal)) {
				continue;
			}

			drawWorkspace1Pixel(rotatedX, rotatedY, getWorkspace2Pixel(x, y));
		}
	}

	for (u32 y = 0; y < diagonal; y++) {
		for (u32 x = 0; x < diagonal; x++) {
			ColorA pixel = getWorkspace1Pixel(x, y);

			if (pixel.a == 0) {
				continue;
			}

			i32 screenX = x + posX - ((f32)diagonal / 2 - bufferWidth * op->dataScale.x / 2);
			i32 screenY = y + posY - ((f32)diagonal / 2 - bufferHeight * op->dataScale.y / 2);

			if (op->screenOnly) {
				if (screenX < 0 || screenX >= m_screenWidth || screenY < 0 || screenY >= m_screenHeight) {
					continue;
				}

				if (m_screenDepth[screenY * m_screenWidth + screenX] > op->zOrder) {
					continue;
				}

				m_screenMutex.lock();
				m_screen[screenY * m_screenWidth + screenX] = blendPixel(pixel, {(u32)screenX, (u32)screenY});
				m_screenDepth[screenY * m_screenWidth + screenX] = op->zOrder;
				m_screenMutex.unlock();
				continue;
			}

			std::for_each(m_cameraOutputs.begin(), m_cameraOutputs.end(), [&](std::pair<u32, std::vector<Color>> output) {
				Camera *camera = getCameraById(output.first);
				if (camera == nullptr || camera->exclude) {
					return;
				}

				if (screenX < 0 || screenX >= m_screenWidth || screenY < 0 || screenY >= m_screenHeight) {
					return;
				}

				if (m_cameraDepth[output.first][screenY * m_screenWidth + screenX] > getZOrder()) {
					return;
				}

				m_cameraDepth[output.first][screenY * m_screenWidth + screenX] = getZOrder();
				output.second[screenY * m_screenWidth + screenX] = blendPixel(pixel, {(u32)screenX, (u32)screenY});
			});
		}
	}
}


void SoftwareRenderer::cameraCreated(u32 id) {
	m_cameraOutputs.insert({id, std::vector<Color>(m_screenWidth * m_screenHeight, Color::Black)});
}

void SoftwareRenderer::cameraDestroyed(u32 id) {
	m_cameraOutputs.erase(id);
}

void SoftwareRenderer::cameraSelected(u32 id) {
	m_cameraSelected = true;
}

void SoftwareRenderer::cameraDeselected() {
	m_cameraSelected = false;
}


void SoftwareRenderer::allocateWorkspace1(u32 width, u32 height) {
	if (m_bufferWorkspaces[0].size() < width * height) {
		m_bufferWorkspaces[0].resize(width * height);
	}
	std::fill(m_bufferWorkspaces[0].begin(), m_bufferWorkspaces[0].end(), ColorA::Clear);
	m_bufferWorkspaceWidth[0] = width;
}

void SoftwareRenderer::drawWorkspace1Pixel(u32 x, u32 y, ColorA color) {
	m_bufferWorkspaces[0][y * m_bufferWorkspaceWidth[0] + x] = color;
}

ColorA SoftwareRenderer::getWorkspace1Pixel(u32 x, u32 y) {
	return m_bufferWorkspaces[0][y * m_bufferWorkspaceWidth[0] + x];
}


void SoftwareRenderer::allocateWorkspace2(u32 width, u32 height) {
	if (m_bufferWorkspaces[1].size() < width * height) {
		m_bufferWorkspaces[1].resize(width * height);
	}
	std::fill(m_bufferWorkspaces[1].begin(), m_bufferWorkspaces[1].end(), ColorA::Clear);
	m_bufferWorkspaceWidth[1] = width;
}

void SoftwareRenderer::drawWorkspace2Pixel(u32 x, u32 y, ColorA color) {
	m_bufferWorkspaces[1][y * m_bufferWorkspaceWidth[1] + x] = color;
}

ColorA SoftwareRenderer::getWorkspace2Pixel(u32 x, u32 y) {
	return m_bufferWorkspaces[1][y * m_bufferWorkspaceWidth[1] + x];
}
