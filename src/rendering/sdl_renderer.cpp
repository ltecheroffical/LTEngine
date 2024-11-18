#ifdef LTENGINE_SDL_ENABLE

#include <LTEngine/rendering/sdl_renderer.hpp>


using namespace LTEngine;
using namespace LTEngine::Rendering;


SDLRenderer::SDLRenderer(SDL_Renderer *renderer) : m_renderer(renderer) {}


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


void SDLRenderer::drawRect(Shapes::Rect rect, ColorA color, RendererFlags flags) {
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);

	worldToScreenPosition(&rect.x, &rect.y);

	SDL_FRect sdlRect = {rect.x, rect.y, (f32)rect.w * getWorldScale().x, (f32)rect.h * getWorldScale().y};
	SDL_RenderFillRectF(m_renderer, &sdlRect);
}

void SDLRenderer::drawCircle(Shapes::Circle circle, ColorA color, RendererFlags flags) {
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);

	worldToScreenPosition(&circle.x, &circle.y);

	u32 centerX = circle.radius + circle.x;
	u32 centerY = circle.radius + circle.y;

	i32 x = circle.radius;
	i32 y = 0;
	i32 p = 1 - circle.radius;

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
		for (u32 y = 0; y < 2 * circle.radius + 1; y++) {
			for (u32 x = 0; x < 2 * circle.radius + 1; x++) {
				// Do not draw outside the circle
				i32 dx = x - circle.radius;
				i32 dy = y - circle.radius;

				if (dx * dx + dy * dy > circle.radius * circle.radius) { continue; }
				SDL_RenderDrawPoint(m_renderer, x, y);
			}
		}
	}
}


void SDLRenderer::drawLine(Math::Vec2 a, Math::Vec2 b, u16 thickness, ColorA color, RendererFlags flags) {
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	if (flags & Renderer::FLAG_FLIP_H || flags & Renderer::FLAG_FLIP_V) { std::swap(a, b); }

	worldToScreenPosition(&a.x, &a.y);
	worldToScreenPosition(&b.x, &b.y);

	// Simulate thickness
	for (u16 i = 0; i < thickness; i++) {
		SDL_RenderDrawLine(m_renderer, a.x - i, a.y - i, b.x - i, b.y - i);
		SDL_RenderDrawLine(m_renderer, a.x, a.y, b.x, b.y);
		SDL_RenderDrawLine(m_renderer, a.x + i, a.y + i, b.x + i, b.y + i);
	}
}

void SDLRenderer::drawPoints(Shapes::Polygon polygon, ColorA color, RendererFlags flags) {
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);

	u32 count = polygon.points.size();
	Math::Vec2 *points = polygon.points.data();

	for (u32 i = 0; i < count; i++) {
		u32 aX = worldToScreenPosition(points[i]).x;
		u32 aY = worldToScreenPosition(points[i]).y;
		u32 bX = points[(i + 1) % count].x;
		u32 bY = points[(i + 1) % count].y;
		SDL_RenderDrawLine(m_renderer, aX, aY, bX, bY);
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
						SDL_RenderDrawPoint(m_renderer, x + min_x, y + min_y);
					}
				}
			}
		}
	}
}


void SDLRenderer::drawImage(const Image *image, Math::Vec2i position, f32 rotation, Shapes::Recti region, ColorA color,
                            RendererFlags flags) {
	SDL_Texture *texture;

	if (!m_imageCache.contains(image)) {
		texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, region.w, region.h);
		if (texture == NULL) { throw std::runtime_error("Failed to create SDL texture! " + std::string(SDL_GetError())); }

		void *pixels;
		int pitch;

		if (SDL_LockTexture(texture, NULL, &pixels, &pitch) == 0) {
			for (u32 y = 0; y < region.h; y++) {


				u8 *row = (u8 *)pixels + y * pitch;
				for (u32 x = 0; x < region.w; x++) {
					row[x * 4] = image->getPixel(x + region.x, y + region.y).r;
					row[x * 4 + 1] = image->getPixel(x + region.x, y + region.y).g;
					row[x * 4 + 2] = image->getPixel(x + region.x, y + region.y).b;
					row[x * 4 + 3] = image->getPixel(x + region.x, y + region.y).a;
				}
			}
			SDL_UnlockTexture(texture);
		} else {
			SDL_DestroyTexture(texture);
			throw std::runtime_error("Failed to lock SDL texture! " + std::string(SDL_GetError()));
		}
		m_imageCache[image] = texture;
	} else {
		texture = m_imageCache[image];
	}

	SDL_Rect rect;
	rect.x = worldToScreenPosition(Math::Vec2(position.x, position.y)).x;
	rect.y = worldToScreenPosition(Math::Vec2(position.x, position.y)).x;
	rect.w = region.w;
	rect.h = region.h;

	SDL_Point center = {(int)region.w / 2, (int)region.h / 2};
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	if (flags & Renderer::FLAG_FLIP_H) { flip = SDL_FLIP_HORIZONTAL; }
	if (flags & Renderer::FLAG_FLIP_V) { flip = SDL_FLIP_VERTICAL; }

	m_imageCacheLifetime[image] = MAX_IMAGE_CACHE_LIFETIME;

	std::erase_if(m_imageCacheLifetime, [this](std::pair<const Image *, u32> pair) {
		if (--pair.second > 0) { return false; }
		SDL_DestroyTexture(m_imageCache[pair.first]);
		const auto it = m_imageCache.find(pair.first);
		if (it != m_imageCache.end()) { m_imageCache.erase(it); }
		return true;
	});

	SDL_RenderCopyEx(m_renderer, texture, &rect, &rect, rotation, &center, flip);
}

#endif
