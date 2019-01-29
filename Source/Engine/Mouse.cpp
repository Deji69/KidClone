#include <Source/pch.h>
#include <SDL.h>
#include <Source/Engine/Config.h>
#include <Source/Engine/Mouse.h>
#include <Source/Engine/Window.h>
#include <Source/Engine/InputImpl.h>

namespace KidClone {

auto Mouse::isButtonPressed(Button button)->bool
{
	return InputImpl::isMouseButtonPressed(button);
}

auto Mouse::getPosition()->Vector2i
{
	return InputImpl::getMousePosition();
}

auto Mouse::getPosition(const Window& relativeTo)->Vector2i
{
	return getPosition() - relativeTo.getPosition();
}

auto Mouse::setPosition(Vector2i pos)->void
{
	return InputImpl::setMousePosition(pos);
}

auto Mouse::setPosition(Vector2i pos, const Window& relativeTo)->void
{
	return InputImpl::setMousePosition(pos, relativeTo);
}

} // namespace KidClone
