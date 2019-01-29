#include <Source/pch.h>
#include <Source/Common.h>
#include <Source/Engine/Window.h>
#include <Source/Engine/SDL/Surface.h>
#include <Source/Engine/SDL/WindowImplSDL.h>
#include <SDL.h>

namespace KidClone {

using namespace SDL;

WindowImplSDL::WindowImplSDL(string_view title, VideoMode mode, uint32 style)
{
	uint32 flags = 0;
	auto width = mode.width;
	auto height = mode.height;

	if (style & Window::Style::Fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	else {
		if (style & Window::Style::Resizable)
			flags |= SDL_WINDOW_RESIZABLE;
	}

	m_handle = SDL_CreateWindow(CStringView(title), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
	setData("windowImpl", this);
}

WindowImplSDL::~WindowImplSDL()
{
	if (m_handle) {
		SDL_DestroyWindow(m_handle);
	}
}

auto WindowImplSDL::getPosition() const->Vector2i
{
	Vector2i vec;
	SDL_GetWindowPosition(m_handle, &vec.x, &vec.y);
	return vec;
}

auto WindowImplSDL::getSize() const->Vector2u
{
	Vector2i vec;
	SDL_GetWindowSize(m_handle, &vec.x, &vec.y);
	return static_cast<Vector2u>(vec);
}

auto WindowImplSDL::getData(string_view name) const->void*
{
	return SDL_GetWindowData(m_handle, CStringView{name});
}

auto WindowImplSDL::hasFocus() const->bool
{
	auto flags = SDL_GetWindowFlags(m_handle);
	return (flags & SDL_WINDOW_INPUT_FOCUS) != 0;
}

auto WindowImplSDL::setPosition(Vector2i vec)->void
{
	SDL_SetWindowPosition(m_handle, vec.x, vec.y);
}

auto WindowImplSDL::setSize(Vector2u vec)->void
{
	SDL_SetWindowSize(m_handle, vec.x, vec.y);
}

auto WindowImplSDL::setTitle(string_view title)->void
{
	SDL_SetWindowTitle(m_handle, CStringView(title));
}

auto WindowImplSDL::setIcon(uint width, uint height, const uint8* pixels)->void
{
	Surface surface(const_cast<uint8*>(pixels), width, height, 32);
	SDL_SetWindowIcon(m_handle, surface.get());
}

auto WindowImplSDL::setVisible(bool visible)->void
{
	if (visible) SDL_ShowWindow(m_handle);
	else SDL_HideWindow(m_handle);
}

auto WindowImplSDL::setCursorVisible(bool visible)->void
{
	SDL_ShowCursor(visible ? SDL_TRUE : SDL_FALSE);
}

auto WindowImplSDL::setMouseGrabbed(bool grab)->void
{
	SDL_SetWindowGrab(m_handle, grab ? SDL_TRUE : SDL_FALSE);
}

auto WindowImplSDL::setData(string_view name, void* data)->void
{
	SDL_SetWindowData(m_handle, CStringView{name}, data);
}

auto WindowImplSDL::requestFocus()->void
{
	SDL_RaiseWindow(m_handle);
}

auto WindowImplSDL::getSystemHandle()->WindowHandle
{
	return m_handle;
}

}
