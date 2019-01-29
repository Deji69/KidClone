#pragma once
#include <Source/Common.h>
#include <Source/Engine/SDL/RendererSDL.h>

struct SDL_Texture;

namespace KidClone {

class TextureSDL : NoCopy {
public:
	virtual ~TextureSDL();
	TextureSDL() = default;
	TextureSDL(SDL_Texture*);
	TextureSDL(TextureSDL&&) noexcept;

	auto operator =(TextureSDL&&) noexcept->TextureSDL&;

	auto get() const->SDL_Texture*;
	auto create(RendererSDL& renderer, uint width, uint height)->bool;

private:
	SDL_Texture* m_texture = nullptr;
	Vector2u m_size = {0, 0};
	bool m_smoothing = false;
};

}
