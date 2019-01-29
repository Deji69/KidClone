#pragma once
#include <Source/Common.h>

namespace KidClone {

class WindowEvent {
public:
	struct SizeEvent {
		uint width;
		uint height;
	};
	struct KeyEvent {
		uint key;
		bool alt;
		bool ctrl;
		bool shift;
		bool system;
	};
	struct TextEvent {
		uint32 unicode;
	};
	struct MouseMoveEvent {
		int x;
		int y;
	};
	struct MouseButtonEvent {
		uint button;
		int x;
		int y;
	};
	struct MouseScrollEvent {
		float delta;
		int x;
		int y;
	};

	enum Type {
		Closed,
		Resized,
		LostFocus,
		GainedFocus,
		TextEntered,
		KeyPressed,
		KeyReleased,
		MouseScrolled,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseEntered,
		MouseLeft,
	};

	Type type;
	union {
		SizeEvent size;
		KeyEvent key;
		TextEvent text;
		MouseMoveEvent mouseMove;
		MouseButtonEvent mouseButton;
		MouseScrollEvent mouseScroll;
	};
};

} // namespace KidClone
