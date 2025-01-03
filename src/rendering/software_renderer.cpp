#include <cmath>

#include <LTEngine/rendering/software_renderer.hpp>


using namespace LTEngine;
using namespace LTEngine::Rendering;


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
	std::for_each(m_cameraDepth.begin(), m_cameraDepth.end(),
	              [width, height](std::pair<u32, std::vector<u16>> output) { output.second.resize(width * height, 0); });
	m_screen.resize(m_screenWidth * m_screenHeight, Color::Black);
	m_screenDepth.resize(m_screenWidth * m_screenHeight, 0);
}


size_t SoftwareRenderer::getScreenData(Color *data) {
	if (data != nullptr) { memcpy(data, m_screen.data(), sizeof(Color) * m_screenWidth * m_screenHeight); }
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

	m_rendererQueueMutex.lock();
	m_rendererQueue.push(op);
	m_rendererQueueMutex.unlock();
}

void SoftwareRenderer::clear(ColorA color) {
	RendererQueueOp op;
	op.opType = RendererQueueOp::RenderOpType::Clear;
	op.screenOnly = m_screenOnly;
	op.color = color;

	m_rendererQueueMutex.lock();
	m_rendererQueue.push(op);
	m_rendererQueueMutex.unlock();
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

	m_rendererQueueMutex.lock();
	m_rendererQueue.push(op);
	m_rendererQueueMutex.unlock();
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

	worldToScreenPosition(&rect.x, &rect.y);
	worldToScreenRotation(&rect.rotation);
	op.dataRect = Shapes::Recti(rect.x, rect.y, rect.w, rect.h);
	op.dataScale = getWorldScale();

	m_rendererQueueMutex.lock();
	m_rendererQueue.push(op);
	m_rendererQueueMutex.unlock();
}

void SoftwareRenderer::drawCircle(Shapes::Circle circle, ColorA color, RendererFlags flags) {
	RendererQueueOp op;
	op.opType = RendererQueueOp::RenderOpType::Circle;
	op.screenOnly = m_screenOnly;
	op.color = color;
	op.zOrder = getZOrder();
	op.flags = flags;

	worldToScreenPosition(&circle.x, &circle.y);
	worldToScreenRotation(&circle.rotation);
	op.dataCircle = circle;

	m_rendererQueueMutex.lock();
	m_rendererQueue.push(op);
	m_rendererQueueMutex.unlock();
}


void SoftwareRenderer::drawLine(Math::Vec2 a, Math::Vec2 b, u16 thickness, ColorA color, RendererFlags flags) {
	RendererQueueOp op;
	op.opType = RendererQueueOp::RenderOpType::Line;
	op.screenOnly = m_screenOnly;
	op.color = color;
	op.zOrder = getZOrder();
	op.flags = flags;

	op.dataPointA = worldToScreenPosition(a);
	op.dataPointB = worldToScreenPosition(b);
	op.dataThickness = thickness;

	op.dataScale = getWorldScale();

	m_rendererQueueMutex.lock();
	m_rendererQueue.push(op);
	m_rendererQueueMutex.unlock();
}

void SoftwareRenderer::drawPoints(Shapes::Polygon polygon, ColorA color, RendererFlags flags) {
	RendererQueueOp op;
	op.opType = RendererQueueOp::RenderOpType::Polygon;
	op.screenOnly = m_screenOnly;
	op.color = color;
	op.zOrder = getZOrder();
	op.flags = flags;

	op.dataScale = getWorldScale();

	worldToScreenRotation(&polygon.rotation);
	op.dataPolygon = polygon;
	for (Math::Vec2 &point : op.dataPolygon.points) { point = worldToScreenPosition(point); }

	m_rendererQueueMutex.lock();
	m_rendererQueue.push(op);
	m_rendererQueueMutex.unlock();
}


void SoftwareRenderer::drawImage(const Image *image, Math::Vec2i position, f32 rotation, Shapes::Recti region, ColorA color,
                                 RendererFlags flags) {
	RendererQueueOp op;
	op.opType = RendererQueueOp::RenderOpType::Image;
	op.screenOnly = m_screenOnly;
	op.color = color;
	op.zOrder = getZOrder();
	op.flags = flags;

	op.dataPosition = worldToScreenPosition((Math::Vec2i){position.x, position.y});
	op.dataRotation = worldToScreenRotation(rotation);
	op.dataRect = region;
	op.dataScale = getWorldScale();
	op.dataImage = image;

	m_rendererQueueMutex.lock();
	m_rendererQueue.push(op);
	m_rendererQueueMutex.unlock();
}

void SoftwareRenderer::drawCamera(u32 id, Shapes::Recti rect, ColorA color, RendererFlags flags) {
	RendererQueueOp op;
	op.opType = RendererQueueOp::RenderOpType::Camera;
	op.screenOnly = m_screenOnly;
	op.color = color;
	op.zOrder = getZOrder();
	op.flags = flags;

	worldToScreenPosition(&rect.x, &rect.y);
	op.dataRect = Shapes::Recti(rect.x, rect.y, rect.w, rect.h);
	op.dataCamId = id;

	m_rendererQueueMutex.lock();
	m_rendererQueue.push(op);
	m_rendererQueueMutex.unlock();
}


bool SoftwareRenderer::process() {
	m_rendererQueueMutex.lock();

	if (m_rendererQueue.empty()) {
		m_rendererQueueMutex.unlock();
		return false;
	}

	RendererQueueOp op = m_rendererQueue.front();
	m_rendererQueue.pop();

	m_rendererQueueMutex.unlock();

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
				              if (camera == nullptr) { return; }
				              if (camera->exclude) { return; }

				              m_cameraMutexes[output.first].lock();
				              const f32 A_n = op.color.a / 255.f;
				              const Color bg = output.second.at(op.dataPosition.y * m_screenWidth + op.dataPosition.x);
				              output.second.at(op.dataPosition.y * m_screenWidth + op.dataPosition.x) = blendColors(op.color, bg);
				              m_cameraMutexes[output.first].unlock();
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
				if (camera == nullptr) { return; }
				if (camera->exclude) { return; }

				m_cameraMutexes[output.first].lock();
				std::fill(output.second.begin(), output.second.end(), op.color);
				std::fill(m_cameraDepth[output.first].begin(), m_cameraDepth[output.first].end(), 0);
				m_cameraMutexes[output.first].unlock();
			});
			break;
		case RendererQueueOp::RenderOpType::ClearA:
			if (op.screenOnly) {
				m_screenMutex.lock();
				std::transform(m_screen.begin(), m_screen.end(), m_screen.begin(),
				               [op, blendColors](Color color) { return blendColors(op.color, color); });
				std::fill(m_screenDepth.begin(), m_screenDepth.end(), 0);
				m_screenMutex.unlock();
				break;
			}
			std::for_each(m_cameraOutputs.begin(), m_cameraOutputs.end(),
			              [this, op, blendColors](std::pair<u32, std::vector<Color>> output) {
				              Camera *camera = getCameraById(output.first);
				              if (camera == nullptr) { return; }
				              if (camera->exclude) { return; }

				              m_cameraMutexes[output.first].lock();
				              std::transform(output.second.begin(), output.second.end(), output.second.begin(),
				                             [op, blendColors](Color color) { return blendColors(op.color, color); });
				              std::fill(m_cameraDepth[output.first].begin(), m_cameraDepth[output.first].end(), 0);
				              m_cameraMutexes[output.first].unlock();
			              });
			break;

		case RendererQueueOp::RenderOpType::Rect:
			prepareBuffer(op.dataRect.w, op.dataRect.h);
			for (u32 y = 0; y < op.dataRect.h; y++) {
				for (u32 x = 0; x < op.dataRect.w; x++) { // Why this order? It's about CPU caching!
					drawBufferPixel(x, y, op.color);
				}
			}
			displayBuffer(op.dataRect.x, op.dataRect.y, &op, op.dataRect.rotation);
			break;
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

							if (dx * dx + dy * dy > radius * radius) { continue; }
							drawBufferPixel(x, y, op.color);
						}
					}
				}


				displayBuffer(op.dataCircle.x - radius - 1, op.dataCircle.y - radius - 1, &op, op.dataCircle.rotation);
				break;
			}
		case RendererQueueOp::RenderOpType::Line:
			{
				u32 width = abs(op.dataPointB.x - op.dataPointA.x) + 1;
				u32 height = abs(op.dataPointB.y - op.dataPointA.y) + 1;

				prepareBuffer(width, height);

				i32 positionX = (op.dataPointA.x < op.dataPointB.x) ? op.dataPointA.x : op.dataPointB.x;
				i32 positionY = (op.dataPointA.y < op.dataPointB.y) ? op.dataPointA.y : op.dataPointB.y;

				op.dataPointA.x -= positionX;
				op.dataPointA.y -= positionY;
				op.dataPointB.x -= positionX;
				op.dataPointB.y -= positionY;

				i32 dx = abs(op.dataPointB.x - op.dataPointA.x);
				i32 dy = abs(op.dataPointB.y - op.dataPointA.y);
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

					if (op.dataPointA.x == op.dataPointB.x && op.dataPointA.y == op.dataPointB.y) { break; }

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
						if (points[i].x < min_x) min_x = points[i].x;
						if (points[i].x > max_x) max_x = points[i].x;
						if (points[i].y < min_y) min_y = points[i].y;
						if (points[i].y > max_y) max_y = points[i].y;
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
								for (i32 x = intersections[i]; x <= intersections[i + 1]; x++) { drawBufferPixel(x, y, op.color); }
							}
						}
					}

					u32 posX = min_x;
					u32 posY = min_y;
					displayBuffer(posX, posY, &op, op.dataPolygon.rotation);
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

				displayBuffer(op.dataPosition.x, op.dataPosition.y, &op, op.dataRotation);
				break;
			}
		case RendererQueueOp::RenderOpType::Camera:
			prepareBuffer(op.dataRect.w, op.dataRect.h);

			for (u32 y = 0; y < op.dataRect.h; y++) {
				for (u32 x = 0; x < op.dataRect.w; x++) {
					drawBufferPixel(x, y,
					                ColorA(m_cameraOutputs.at(op.dataCamId).at(y * m_screenWidth + x).r,
					                       m_cameraOutputs.at(op.dataCamId).at(y * m_screenWidth + x).g,
					                       m_cameraOutputs.at(op.dataCamId).at(y * m_screenWidth + x).b, 255));
				}
			}

			displayBuffer(op.dataRect.x, op.dataRect.y, &op, op.dataRect.rotation);
			break;

		default:
			break;
	}

	return true;
}

void SoftwareRenderer::processAll() {
	// Yes, it's dead simple
	while (process());
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
	m_bufferWidth = width;
	m_bufferHeight = height;
	if (m_bufferData.size() < m_bufferWidth * m_bufferHeight) { m_bufferData.resize(m_bufferWidth * m_bufferHeight); }
	std::fill(m_bufferData.begin(), m_bufferData.end(), ColorA::Clear);
}

void SoftwareRenderer::drawBufferPixel(u32 x, u32 y, ColorA color) {
	m_bufferData[y * m_bufferWidth + x] = color;
}

void SoftwareRenderer::displayBuffer(i32 posX, i32 posY, const RendererQueueOp *op, f32 rotation) {
	if (m_screenOnly && m_cameraSelected) { return; }

	const auto blendPixel = [this, op, &posX, &posY](ColorA color, Math::Vec2u texturePosition) -> Color {
		Color bg = m_screen[(texturePosition.y + posY) * m_screenWidth + (texturePosition.x + posX)];
		const f32 A_n = color.a / 255.f;

		f32 out_r = color.r * A_n + bg.r * (1.f - A_n);
		f32 out_g = color.g * A_n + bg.g * (1.f - A_n);
		f32 out_b = color.b * A_n + bg.b * (1.f - A_n);

		return Color(out_r, out_g, out_b);
	};

	if (m_bufferWorkspace1.size() < m_bufferWidth * m_bufferHeight) { m_bufferWorkspace1.resize(m_bufferWidth * m_bufferHeight); }

	for (u32 y = 0; y < m_bufferHeight; y++) {
		for (u32 x = 0; x < m_bufferWidth; x++) {
			ColorA color = m_bufferData[y * m_bufferWidth + x];
			if (op->shader != nullptr) {
				CPUShaderIO io = {.position = Math::Vec2i(posX, posY),
				                  .color = op->color,

				                  .screen = m_screen.data(),
				                  .screenSize = {m_screenWidth, m_screenHeight},

				                  .texture = m_bufferData.data(),
				                  .textureWidth = m_bufferWidth,
				                  .textureHeight = m_bufferHeight,
				                  .textureX = x,
				                  .textureY = y,

				                  .time = (op->timestamp.time_since_epoch().count() - m_creationTime.time_since_epoch().count()) /
				                          1000000000.f};

				op->shader->fragment(&io);

				color = io.color;
				posX = io.position.x;
				posY = io.position.y;
			}
			m_bufferWorkspace1[y * m_bufferWidth + x] = color;
		}
	}

	if (m_bufferWorkspace2.size() < (m_bufferWidth * op->dataScale.x) * (m_bufferHeight * op->dataScale.y)) {
		m_bufferWorkspace2.resize((m_bufferWidth * op->dataScale.x) * (m_bufferHeight * op->dataScale.y));
	}

	switch (m_scalingMode) {
		case ScalingMode::Nearest:
			for (u32 y = 0; y < m_bufferHeight * op->dataScale.y; y++) {
				for (u32 x = 0; x < m_bufferWidth * op->dataScale.x; x++) {
					m_bufferWorkspace2[y * (m_bufferWidth * getWorldScale().x) + x] =
					    m_bufferWorkspace1[y / op->dataScale.y * m_bufferWidth + x / op->dataScale.x];
				}
			}
			break;
		case ScalingMode::Linear:
			// Uh oh... (This requires lots of math)
			for (u32 y = 0; y < m_bufferHeight * op->dataScale.y; y++) {
				for (u32 x = 0; x < m_bufferWidth * op->dataScale.x; x++) {
					f32 origX = x / op->dataScale.x;
					f32 origY = y / op->dataScale.y;

					u32 x1 = static_cast<u32>(std::floor(origX));
					u32 y1 = static_cast<u32>(std::floor(origY));
					u32 x2 = std::min(x1 + 1, m_bufferWidth - 1);
					u32 y2 = std::min(y1 + 1, m_bufferHeight - 1);

					f32 xLerp = origX - x1;
					f32 yLerp = origY - y1;

					ColorA topLeft = m_bufferWorkspace1[y1 * m_bufferWidth + x1];
					ColorA topRight = m_bufferWorkspace1[y1 * m_bufferWidth + x2];
					ColorA bottomLeft = m_bufferWorkspace1[y2 * m_bufferWidth + x1];
					ColorA bottomRight = m_bufferWorkspace1[y2 * m_bufferWidth + x2];

					ColorA topRow = {static_cast<u8>(topLeft.r + xLerp * (topRight.r - topLeft.r)),
					                 static_cast<u8>(topLeft.g + xLerp * (topRight.g - topLeft.g)),
					                 static_cast<u8>(topLeft.b + xLerp * (topRight.b - topLeft.b)),
					                 static_cast<u8>(topLeft.a + xLerp * (topRight.a - topLeft.a))};

					ColorA bottomRow = {static_cast<u8>(bottomLeft.r + xLerp * (bottomRight.r - bottomLeft.r)),
					                    static_cast<u8>(bottomLeft.g + xLerp * (bottomRight.g - bottomLeft.g)),
					                    static_cast<u8>(bottomLeft.b + xLerp * (bottomRight.b - bottomLeft.b)),
					                    static_cast<u8>(bottomLeft.a + xLerp * (bottomRight.a - bottomLeft.a))};

					m_bufferWorkspace2[y * (m_bufferWidth * op->dataScale.x) + x] = {
					    static_cast<u8>(topRow.r + yLerp * (bottomRow.r - topRow.r)),
					    static_cast<u8>(topRow.g + yLerp * (bottomRow.g - topRow.g)),
					    static_cast<u8>(topRow.b + yLerp * (bottomRow.b - topRow.b)),
					    static_cast<u8>(topRow.a + yLerp * (bottomRow.a - topRow.a))};
				}
			}
			break;
	}

	if (m_bufferWorkspace1.size() < (m_bufferWidth * op->dataScale.x) * (m_bufferHeight * op->dataScale.y)) {
		m_bufferWorkspace1.resize((m_bufferWidth * op->dataScale.x) * (m_bufferHeight * op->dataScale.y));
	}

	std::fill(m_bufferWorkspace1.begin(), m_bufferWorkspace1.end(), ColorA::Clear);

	for (u32 x = 0; x < m_bufferWidth * op->dataScale.x; x++) {
		for (u32 y = 0; y < m_bufferHeight * op->dataScale.y; y++) {
			/* According to some SO guy (https://stackoverflow.com/a/13476713/22126820), we can get
			 x_rotated from x * cos(angle) - y * sin(angle)
			 and y_rotated from x * sin(angle) + y * cos(angle) */
			i32 rotatedX = x * cos(rotation) - y * sin(rotation);
			i32 rotatedY = x * sin(rotation) + y * cos(rotation);

			if (rotatedX < 0 || rotatedX >= m_bufferWidth * op->dataScale.x || rotatedY < 0 ||
			    rotatedY >= m_bufferHeight * op->dataScale.y) {
				continue;
			}

			m_bufferWorkspace1[rotatedY * (m_bufferWidth * op->dataScale.x) + rotatedX] =
			    m_bufferWorkspace2[y * (m_bufferWidth * op->dataScale.x) + x];
		}
	}

	for (u32 y = 0; y < m_bufferHeight * op->dataScale.y; y++) {
		for (u32 x = 0; x < m_bufferWidth * op->dataScale.x; x++) {
			if (op->screenOnly) {
				if (x + posX < 0 || x + posX >= m_screenWidth || y + posY < 0 || y + posY >= m_screenHeight) { continue; }

				if (m_screenDepth[(y + posY) * m_screenWidth + (x + posX)] > op->zOrder) { continue; }

				m_screenMutex.lock();
				m_screen[((y + posY) * m_screenWidth + (x + posX))] = blendPixel(m_bufferWorkspace1[y * m_bufferWidth + x], {x, y});
				m_screenDepth[(y + posY) * m_screenWidth + (x + posX)] = op->zOrder;
				m_screenMutex.unlock();
				continue;
			}
			std::for_each(m_cameraOutputs.begin(), m_cameraOutputs.end(), [&](std::pair<u32, std::vector<Color>> output) {
				Camera *camera = getCameraById(output.first);
				if (camera == nullptr) { return; }
				if (camera->exclude) { return; }

				if (m_cameraDepth[output.first][(y + posY) * m_screenWidth + (x + posX)] > getZOrder()) { return; }

				m_cameraMutexes[output.first].lock();
				m_cameraDepth[output.first][(y + posY) * m_screenWidth + (x + posX)] = getZOrder();
				output.second[(y + posY) * m_screenWidth + (x + posX)] =
				    blendPixel(m_bufferWorkspace1[y * m_bufferWidth + x], {x, y});
				m_cameraMutexes[output.first].unlock();
			});
		}
	}

	/*
	for (u32 y = 0; y < m_bufferHeight; y++) {
	    for (u32 x = 0; x < m_bufferWidth; x++) {
	        if (op->screenOnly) {
	            if (x + posX < 0 || x + posX >= m_screenWidth || y + posY < 0 || y + posY >= m_screenHeight) { continue; }

	            if (m_screenDepth[(y + posY) * m_screenWidth + (x + posX)] > op->zOrder) { continue; }

	            m_screenMutex.lock();
	            m_screen[((y + posY) * m_screenWidth + (x + posX))] = processPixel(m_bufferData[y * m_bufferWidth + x], {x, y});
	            m_screenDepth[(y + posY) * m_screenWidth + (x + posX)] = op->zOrder;
	            m_screenMutex.unlock();
	            continue;
	        }
	        std::for_each(m_cameraOutputs.begin(), m_cameraOutputs.end(), [&](std::pair<u32, std::vector<Color>> output) {
	            Camera *camera = getCameraById(output.first);
	            if (camera == nullptr) { return; }
	            if (camera->exclude) { return; }

	            if (m_cameraDepth[output.first][(y + posY) * m_screenWidth + (x + posX)] > getZOrder()) { return; }

	            m_cameraMutexes[output.first].lock();
	            m_cameraDepth[output.first][(y + posY) * m_screenWidth + (x + posX)] = getZOrder();
	            output.second[(y + posY) * m_screenWidth + (x + posX)] = processPixel(m_bufferData[y * m_bufferWidth + x], {x, y});
	            m_cameraMutexes[output.first].unlock();
	        });
	    }
	}*/
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
