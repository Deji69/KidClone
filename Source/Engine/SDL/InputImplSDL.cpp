#include <Source/pch.h>
#include <SDL.h>
#include <Source/Engine/Window.h>
#include "InputImplSDL.h"

namespace KidClone {

auto InputImpl::isMouseButtonPressed(Mouse::Button button)->bool
{
	auto state = SDL_GetMouseState(nullptr, nullptr);
	switch (button) {
	case Mouse::Left:
		return state & SDL_BUTTON(SDL_BUTTON_LEFT);
	case Mouse::Right:
		return state & SDL_BUTTON(SDL_BUTTON_RIGHT);
	case Mouse::Middle:
		return state & SDL_BUTTON(SDL_BUTTON_MIDDLE);
	case Mouse::XButton1:
		return state & SDL_BUTTON(SDL_BUTTON_X1);
	case Mouse::XButton2:
		return state & SDL_BUTTON(SDL_BUTTON_X2);
	}
	return false;
}

auto InputImpl::getMousePosition()->Vector2i {
	int x, y;
	SDL_GetMouseState(&x, &y);
	return {x, y};
}

auto InputImpl::setMousePosition(Vector2i pos)->void
{
	SDL_WarpMouseGlobal(pos.x, pos.y);
}

auto InputImpl::setMousePosition(Vector2i pos, const Window& relativeTo)->void
{
	SDL_WarpMouseInWindow(relativeTo.getSystemHandle(), pos.x, pos.y);
}

} // namespace KidClone
