#ifdef LTENGINE_SDL_ENABLE

#include <LTEngine/rendering/sdl_renderer.hpp>


using namespace LTEngine;
using namespace LTEngine::Rendering;


SDLRenderer::SDLRenderer(SDL_Renderer *renderer) : m_renderer(renderer) {
}


void SDLRenderer::clear(Color color) {
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, 255);
    SDL_RenderClear(m_renderer);
}

void SDLRenderer::clear(ColorA color) {
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(m_renderer);
}


void SDLRenderer::setPixel(Math::Vec2i position, Color color) {
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, 255);
    SDL_RenderDrawPoint(m_renderer, position.x, position.y);
}

void SDLRenderer::setPixel(Math::Vec2i position, ColorA color) {
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoint(m_renderer, position.x, position.y);
}

Color SDLRenderer::getPixel(Math::Vec2i position) {
    Color color;
    SDL_GetRenderDrawColor(m_renderer, &color.r, &color.g, &color.b, nullptr);
    return color;
}


void SDLRenderer::drawRect(Math::Rect rect, ColorA color, RendererFlags flags) {
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);

    SDL_FRect sdlRect = {rect.x + m_positionOffset.x, rect.y + m_positionOffset.y, (f32)rect.w, (f32)rect.h};
    SDL_RenderFillRectF(m_renderer, &sdlRect);
}

void SDLRenderer::drawCircle(Math::Vec2 centerPosition, f32 radius, ColorA color, RendererFlags flags) {
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);

    u32 centerX = radius + centerPosition.x + m_positionOffset.x;
    u32 centerY = radius + centerPosition.y + m_positionOffset.y;

    i32 x = radius;
    i32 y = 0;
    i32 p = 1 - radius;

    while (x >= y) {
        SDL_RenderDrawPoint(m_renderer, centerX + x, centerY + y);
        SDL_RenderDrawPoint(m_renderer, centerX + x, centerY - y);
        SDL_RenderDrawPoint(m_renderer, centerX - x, centerY + y);
        SDL_RenderDrawPoint(m_renderer, centerX - x, centerY - y);
        SDL_RenderDrawPoint(m_renderer, centerX + y, centerY + x);
        SDL_RenderDrawPoint(m_renderer, centerX + y, centerY - x);
        SDL_RenderDrawPoint(m_renderer, centerX - y, centerY + x);
        SDL_RenderDrawPoint(m_renderer, centerX - y, centerY - x);

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
                SDL_RenderDrawPoint(m_renderer, x + m_positionOffset.x, y + m_positionOffset.y);
            }
        }
    }
}


void SDLRenderer::drawLine(Math::Vec2 a, Math::Vec2 b, u16 thickness, ColorA color, RendererFlags flags) {
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(m_renderer, a.x + m_positionOffset.x, a.y + m_positionOffset.y, b.x + m_positionOffset.x, b.y + m_positionOffset.y);
}

void SDLRenderer::drawPoints(const Math::Vec2 *points, u32 count, ColorA color, RendererFlags flags) {
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);

    for (u32 i = 0; i < count; i++) {
        u32 aX = points[i].x;
        u32 aY = points[i].y;
        u32 bX = points[(i + 1) % count].x;
        u32 bY = points[(i + 1) % count].y;
        SDL_RenderDrawLine(m_renderer, aX + m_positionOffset.x, aY + m_positionOffset.y, bX + m_positionOffset.x, bY + m_positionOffset.y);
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
                        SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
                        SDL_RenderDrawPoint(m_renderer, x + min_x + m_positionOffset.x, y + min_y + m_positionOffset.y);
                    }
                }
            }
        }
    }
}


void SDLRenderer::drawImage(const Image *image, Math::Vec2i position, ColorA color, RendererFlags flags) {
}

#endif
