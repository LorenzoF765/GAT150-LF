#include "Renderer.h"
#include <SDL.h>
#include <SDL_ttf.h> 
#include <SDL_image.h>
#include "Math/Transform.h"

namespace Solas
{
	void Renderer::Initialize()
	{
		SDL_Init(SDL_INIT_VIDEO);
		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
		TTF_Init();
	}
	void Renderer::ShutDown() // Shutdown is often in opposite order of initialization
	{
		SDL_DestroyRenderer(renderer_);
		SDL_DestroyWindow(window_);
		TTF_Quit();
		IMG_Quit();
	}
	void Renderer::CreateWindow(const char* title, int width, int height)
	{
		width_ = width;
		height_ = height;

		window_ = SDL_CreateWindow(title, 100, 100, width_, height_, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	}
	void Renderer::BeginFrame()
	{
		SDL_SetRenderDrawColor(renderer_, clearColor_.r, clearColor_.g, clearColor_.b, clearColor_.a);
		SDL_RenderClear(renderer_);
	}
	void Renderer::EndFrame()
	{
		SDL_RenderPresent(renderer_);
	}
	void Renderer::DrawLine(float x1, float y1, float x2, float y2)
	{
		SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
		SDL_RenderDrawLineF(renderer_, x1, y1, x2, y2);
	}
	void Renderer::DrawPoint(float x, float y)
	{
		SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0);
		SDL_RenderDrawPointF(renderer_, x, y);
	}
	void Renderer::DrawLine(const Vector2& v1, const Vector2& v2, const Color& color)
	{
		SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
		SDL_RenderDrawLineF(renderer_, v1.x, v1.y, v2.x, v2.y);
	}
	void Renderer::DrawPoint(const Vector2& v, const Color& color)
	{
		SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
		SDL_RenderDrawPointF(renderer_, v.x, v.y);
	}
	void Renderer::Draw(std::shared_ptr<Texture> texture, const Vector2& position, float angle, const Vector2& scale, const Vector2& registration)
	{
		Vector2 size = texture->GetSize();
		size *= scale;
		Vector2 origin = size * registration;
		Vector2 tposition = position - (size * registration);

		SDL_Rect dest;
		dest.x = tposition.x;
		dest.y = tposition.y;
		dest.w = (int)size.x;
		dest.h = (int)size.y;

		SDL_Point center{ (int)origin.x, (int)origin.y };

		SDL_RenderCopyEx(renderer_, texture->texture_, nullptr, &dest, angle, &center, SDL_FLIP_HORIZONTAL);
	}
	void Renderer::Draw(std::shared_ptr<Texture> texture, const Transform& transform, const Vector2& registration)
	{
		Vector2 size = texture->GetSize();
		size *= transform.scale;
		Vector2 origin = size * registration;
		Vector2 tposition = transform.position - (size * registration);

		SDL_Rect dest;
		dest.x = tposition.x;
		dest.y = tposition.y;
		dest.w = (int)size.x;
		dest.h = (int)size.y;

		SDL_Point center{ origin.x, origin.y };

		SDL_RenderCopyEx(renderer_, texture->texture_, nullptr, &dest, transform.rotation, &center, SDL_FLIP_HORIZONTAL);
	}
}