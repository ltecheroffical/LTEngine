#include <LTEngine/rendering/software_renderer.hpp>


using namespace LTEngine;
using namespace LTEngine::Rendering;


SoftwareRenderer::SoftwareRenderer(u32 width, u32 height) : m_screenWidth(width), m_screenHeight(height) {
    m_screen.resize(m_screenWidth * m_screenHeight, Color::BLACK);
}


void SoftwareRenderer::resize(u32 width, u32 height) {
    m_screenWidth = width;
    m_screenHeight = height;
    m_screen.resize(m_screenWidth * m_screenHeight, Color::BLACK);
}


u32 SoftwareRenderer::getScreenData(Color *data) {
    if (data != nullptr) {
        memcpy(data, m_screen.data(), sizeof(Color) * m_screenWidth * m_screenHeight);
    }
    return m_screen.size() * sizeof(Color);
}


void SoftwareRenderer::clear(Color color) {
    std::fill(m_screen.begin(), m_screen.end(), color);
}

void SoftwareRenderer::clear(ColorA color) {
    std::transform(m_screen.begin(), m_screen.end(), m_screen.begin(), [color](Color bg) {
        const f32 A_n = color.a / 255.f;
        return Color(color.r * A_n, color.g * A_n, color.b * A_n) + (bg * (1.f - A_n));
    });
}


void SoftwareRenderer::setPixel(Math::Vec2i position, Color color) {
    m_screen.at(position.y * m_screenWidth + position.x) = color;
}

void SoftwareRenderer::setPixel(Math::Vec2i position, ColorA color) {
    Color bg = m_screen.at(position.y * m_screenWidth + position.x);
    const f32 A_n = color.a / 255.f;
    m_screen.at(position.y * m_screenWidth + position.x) = Color(color.r * A_n, color.g * A_n, color.b * A_n) + (bg * (1.f - A_n));
}

Color SoftwareRenderer::getPixel(Math::Vec2i position) {
    return m_screen.at(position.y * m_screenWidth + position.x);
}


void SoftwareRenderer::drawRect(Math::Rect rect, ColorA color, RendererFlags flags) {
    prepareBuffer(rect.w, rect.h);

    for (u32 y = 0; y < rect.h; y++) {
        for (u32 x = 0; x < rect.w; x++) {
            drawBufferPixel(x, y, color);
        }
    }

    flushBuffer(rect.x, rect.y);
}

void SoftwareRenderer::drawCircle(Math::Vec2 centerPosition, f32 radius, ColorA color, RendererFlags flags) {
    prepareBuffer(2 * radius + 1, 2 * radius + 1);

    u32 centerX = radius;
    u32 centerY = radius;

    i32 x = radius;
    i32 y = 0;
    i32 p = 1 - radius;

    while (x >= y) {
        drawBufferPixel(centerX + x, centerY + y, color);
        drawBufferPixel(centerX + x, centerY - y, color);
        drawBufferPixel(centerX - x, centerY + y, color);
        drawBufferPixel(centerX - x, centerY - y, color);
        drawBufferPixel(centerX + y, centerY + x, color);
        drawBufferPixel(centerX + y, centerY - x, color);
        drawBufferPixel(centerX - y, centerY + x, color);
        drawBufferPixel(centerX - y, centerY - x, color);

        if (p <= 0) {
            p += 2 * ++y + 1;
        } else {
            p += 2 * (++y - --x) + 1;
        }
    }


    if (flags & Renderer::FLAG_FILL) {
        for (u32 y = 0; y < 2 * radius + 1; y++) {
            for (u32 x = 0; x < 2 * radius + 1; x++) {
                // Do not draw outside the circle
                i32 dx = x - radius;
                i32 dy = y - radius;

                if (dx * dx + dy * dy > radius * radius) {
                    continue;
                }
                drawBufferPixel(x, y, color);
            }
        }
    }


    flushBuffer(centerPosition.x - radius - 1, centerPosition.y - radius - 1);
}


void SoftwareRenderer::drawLine(Math::Vec2 a, Math::Vec2 b, u16 thickness, ColorA color, RendererFlags flags) {
    u32 width = abs(b.x - a.x) + 1;
    u32 height = abs(b.y - a.y) + 1;

    prepareBuffer(width, height);

    i32 positionX = (a.x < b.x) ? a.x : b.x;
    i32 positionY = (a.y < b.y) ? a.y : b.y;

    a.x -= positionX;
    a.y -= positionY;
    b.x -= positionX;
    b.y -= positionY;

    i32 dx = abs(b.x - a.x);
    i32 dy = abs(b.y - a.y);
    i32 sx = (a.x < b.x) ? 1 : -1;
    i32 sy = (a.y < b.y) ? 1 : -1;
    i32 err = dx - dy;

    while (true) {
        for (i32 dx = -thickness; dx <= thickness / 2; dx++) {
            for (i32 dy = -thickness; dy <= thickness / 2; dy++) {
                if (a.x + dx < 0 || a.x + dx >= width || a.y + dy < 0 || a.y + dy >= height) {
                    continue;
                }
                drawBufferPixel(a.x + dx, a.y + dy, color);
            }
        }
        
        if (a.x == b.x && a.y == b.y) {
            break;
        }

        i32 e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            a.x += sx;
        }
        if (e2 < dx) {
            err += dx;
            a.y += sy;
        }
    }

    flushBuffer(positionX, positionY);

}

void SoftwareRenderer::drawPoints(const Math::Vec2 *points, u32 count, ColorA color, RendererFlags flags) {
    for (u32 i = 0; i < count; i++) {
        Math::Vec2 point_a = points[i];
        Math::Vec2 point_b = points[(i + 1) % count];

        drawLine(point_a, point_b, 1, color, flags);
    }

    if (flags & Renderer::FLAG_FILL) {
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
                    for (i32 x = intersections[i]; x <= intersections[i + 1]; x++) {
                        drawBufferPixel(x, y, color);
                    }
                }
            }
        }

        u32 posX = min_x;
        u32 posY = min_y;
        flushBuffer(posX, posY);
    } 
}


void SoftwareRenderer::drawImage(const Image *image, Math::Vec2i position, ColorA color, RendererFlags flags) {
    u32 imageWidth = image->getSize().x;
    u32 imageHeight = image->getSize().y;

    prepareBuffer(imageWidth, imageHeight);

    for (u32 y = 0; y < imageHeight; y++) {
        for (u32 x = 0; x < imageWidth; x++) {
            drawBufferPixel(x, y, image->getPixel(x, y));
        }
    }

    flushBuffer(position.x, position.y);
}

void SoftwareRenderer::drawCamera(u32 id, Math::Recti rect, ColorA color, RendererFlags flags) {
    // TODO: Implment this
    // WARN: This is painful to implement
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
    m_bufferData.resize(width * height, ColorA::BLACK);
}

void SoftwareRenderer::drawBufferPixel(u32 x, u32 y, ColorA color) {
    m_bufferData[y * m_bufferWidth + x] = color;
}

void SoftwareRenderer::flushBuffer(i32 posX, i32 posY) {
    for (u32 y = 0; y < m_bufferHeight; y++) {
        for (u32 x = 0; x < m_bufferWidth; x++) {
            if (x + posX < 0 || x + posX >= m_screenWidth || y + posY < 0 || y + posY >= m_screenHeight) {
                continue;
            }

            ColorA color = m_bufferData[y * m_bufferWidth + x];
            if (m_shader != nullptr) {
                CPUShaderIO io = {
                    .position = Math::Vec2i(posX, posY),
                    .color = color,
                    
                    .screen = m_screen.data(),
                    .screenSize = {m_screenWidth, m_screenHeight},
                    
                    .texture = m_bufferData.data(),
                    .textureWidth = m_bufferWidth,
                    .textureHeight = m_bufferHeight,
                    .textureX = x,
                    .textureY = y,
                };
                
                m_shader->fragment(&io);

                color = io.color;
                posX = io.position.x;
                posY = io.position.y;
            }

            Color bg = m_screen[(y + posY) * m_screenWidth + (x + posX)];
            const f32 A_n = color.a / 255.f;
            m_screen[((y + posY) * m_screenWidth + (x + posX))] = Color(color.r * A_n, color.g * A_n, color.b * A_n) + (bg * (1.f - A_n));
        }
    }
}
