#pragma once
#include <Source/Common.h>
#include <Source/Engine/Window.h>

struct SDL_Renderer;

namespace KidClone {

using RendererHandle = SDL_Renderer*;

class RendererSDL {
public:
	RendererSDL(Window&);
	virtual ~RendererSDL();

	auto getHandle()->RendererHandle;
	auto setDrawColour(Colour colour)->void;
	auto setLogicalSize(uint width, uint height)->void;
	auto clear()->void;
	auto display()->void;

private:
	RendererHandle m_renderer;
};

} // namespace KidClone
