#pragma once
#include <SDL.h>
#include <Source/Common.h>
#include <Source/Engine/Mouse.h>

namespace KidClone {

class Window;

class InputImpl {
public:
	static auto isMouseButtonPressed(Mouse::Button)->bool;
	static auto getMousePosition()->Vector2i;
	static auto setMousePosition(Vector2i)->void;
	static auto setMousePosition(Vector2i, const Window&)->void;
};

} // namespace KidClone
