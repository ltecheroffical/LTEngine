#ifndef _LTENGINE_RENDERING_SDL_RENDERER_HPP_
#define _LTENGINE_RENDERING_SDL_RENDERER_HPP_
#ifdef LTENGINE_SDL_ENABLE

#include <unordered_map>

#include <SDL2/SDL.h>

#include <LTEngine/rendering/renderer.hpp>


namespace LTEngine::Rendering {
	class SDLRenderer : public Renderer {
	public:
		SDLRenderer(SDL_Renderer *renderer);
		~SDLRenderer() override = default;

		void clear(Color color) override;
		void clear(ColorA color) override;

		void setPixel(Math::Vec2i position, Color color) override;
		void setPixel(Math::Vec2i position, ColorA color) override;
		Color getPixel(Math::Vec2i position) override;

		void drawRect(Shapes::Rect rect, ColorA color, RendererFlags flags) override;
		void drawCircle(Shapes::Circle, ColorA color, RendererFlags flags) override;

		void drawLine(Math::Vec2 a, Math::Vec2 b, u16 thickness, ColorA color, RendererFlags flags) override;
		void drawPoints(Shapes::Polygon polygon, ColorA color, RendererFlags flags) override;

		void drawImage(const Image *image, Math::Vec2i position, f32 rotation, Shapes::Recti region, ColorA color,
		               RendererFlags flags) override;

	private:
		const u32 MAX_IMAGE_CACHE_LIFETIME = 500;

		std::unordered_map<const Image *, u32> m_imageCacheLifetime;
		std::unordered_map<const Image *, SDL_Texture *> m_imageCache;
		SDL_Renderer *m_renderer;
	};
} // namespace LTEngine::Rendering

#endif
#endif
