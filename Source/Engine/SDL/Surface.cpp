#include <Source/pch.h>
#include <SDL.h>
#include "Surface.h"

namespace KidClone {

namespace SDL {
	Surface::Surface(void* pixels, int width, int height, int depth, int pitch, uint Rmask, uint Gmask, uint Bmask, uint Amask) :
		m_handle(SDL_CreateRGBSurfaceFrom(pixels, width, height, depth, pitch, Rmask, Gmask, Bmask, Amask))
	{
	}

	Surface::Surface(void* pixels, int width, int height, int depth, int pitch, bool alpha) :
		Surface(pixels, width, height, depth, pitch, /*0xFF0000, 0xFF00, 0xFF*/0, 0, 0, alpha ? 0xFF000000 : 0)
	{
	}

	Surface::Surface(SDL_Surface* handle) : m_handle(handle)
	{
	}

	Surface::Surface(Surface&& other) noexcept : m_handle(other.m_handle)
	{
		other.m_handle = nullptr;
	}

	Surface::~Surface()
	{
		if (m_handle != nullptr)
			SDL_FreeSurface(m_handle);
	}

	auto Surface::operator =(Surface&& other) noexcept->Surface&
	{
		if (&other == this)
			return *this;
		if (m_handle != nullptr)
			SDL_FreeSurface(m_handle);
		m_handle = other.m_handle;
		other.m_handle = nullptr;
		return *this;
	}

	auto Surface::get() const->SDL_Surface*
	{
		return m_handle;
	}
}

}