#include <Source/pch.h>
#include <Source/Engine/SDL/RendererSDL.h>
#include <SDL.h>

namespace KidClone {

RendererSDL::RendererSDL(Window& window) :
	m_renderer(SDL_CreateRenderer(window.getSystemHandle(), -1, 0))
{
}

RendererSDL::~RendererSDL()
{
	SDL_DestroyRenderer(m_renderer);
}

auto RendererSDL::getHandle()->RendererHandle
{
	return m_renderer;
}

auto RendererSDL::setDrawColour(Colour colour)->void
{
	SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
}

auto RendererSDL::setLogicalSize(uint width, uint height)->void
{
	SDL_RenderSetLogicalSize(m_renderer, 640, 480);
}

auto RendererSDL::clear()->void
{
	SDL_RenderClear(m_renderer);
}

auto RendererSDL::display()->void
{
	SDL_RenderPresent(m_renderer);
}

} // namespace KidClone
