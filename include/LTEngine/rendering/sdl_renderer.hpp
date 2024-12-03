#ifndef _LTENGINE_RENDERING_SDL_RENDERER_HPP_
#define _LTENGINE_RENDERING_SDL_RENDERER_HPP_
#ifdef LTENGINE_SDL_ENABLE

#include <unordered_map>

#include <SDL2/SDL.h>

#include <LTEngine/rendering/renderer.hpp>

#include <LTEngine/common/compiler_utils.h>


namespace LTEngine::Rendering {
	class LTENGINE_API SDLRenderer : public Renderer {
	public:
		SDLRenderer(SDL_Renderer *renderer);
		~SDLRenderer() override;

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
		Math::Vec2 rotatePosition(Math::Vec2 position, Math::Vec2 center, f32 angle) {
			Math::Vec2 result;
			result.x = center.x + (position.x - center.x) * cos(angle) - (position.y - center.y) * sin(angle);
			result.y = center.y + (position.x - center.x) * sin(angle) + (position.y - center.y) * cos(angle);
			return result;
		}

		const u32 MAX_IMAGE_CACHE_LIFETIME = 5000;

		SDL_Texture *m_squareTexture; // SDL can't rotate squares 💀, something that should be very basic

		std::unordered_map<const Image *, u32> m_imageCacheLifetime;
		std::unordered_map<const Image *, SDL_Texture *> m_imageCache;
		SDL_Renderer *m_renderer;
	};
} // namespace LTEngine::Rendering

#endif
#endif
