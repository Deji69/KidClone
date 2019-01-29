#pragma once
#include <Source/Common.h>

namespace KidClone {

class Window;

class Mouse {
public:
	enum Button {
		Left,
		Right,
		Middle,
		XButton1,
		XButton2,
	};
	enum Wheel {
		VerticalWheel,
		HorizontalWheel,
	};

	static auto isButtonPressed(Button)->bool;
	static auto getPosition()->Vector2i;
	static auto getPosition(const Window& relativeTo)->Vector2i;
	static auto setPosition(Vector2i)->void;
	static auto setPosition(Vector2i, const Window& relativeTo)->void;
};

} // namespace KidClone
