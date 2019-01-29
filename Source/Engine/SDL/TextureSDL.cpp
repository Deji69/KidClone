#include <Source/pch.h>
#include <Source/Engine/SDL/TextureSDL.h>
#include <SDL.h>

namespace KidClone {

TextureSDL::~TextureSDL()
{
	if (m_texture)
		SDL_DestroyTexture(m_texture);
}

auto TextureSDL::get() const->SDL_Texture*
{
	return m_texture;
}

auto TextureSDL::create(RendererSDL& renderer, uint width, uint height)->bool
{
	m_texture = SDL_CreateTexture(renderer.getHandle(), SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, static_cast<int>(width), static_cast<int>(height));
	if (!m_texture) {
		error() << "Failed to create texture: " << SDL_GetError();
		return false;
	}
	return true;
}

} // namespace KidClone
