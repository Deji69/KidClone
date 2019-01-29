#pragma once
#include <Source/Common.h>

namespace KidClone {

class Window;

class EngineEvent {
public:
	enum Type {
		Quit,
		KeyDown,
		KeyUp,
		MouseMove,
		MouseButtonDown,
		MouseButtonUp,
		MouseWheel,
		WindowMove,
		WindowResize,
		WindowClose,
		WindowGainFocus,
		WindowLoseFocus,
		WindowMouseEnter,
		WindowMouseLeave,
		WindowShow,
		WindowHide,
	};

	struct WindowEvent {
		Window* window;
	};
	struct WindowResizeEvent : public WindowEvent {
		uint width;
		uint height;
	};
	struct WindowMoveEvent : public WindowEvent {
		uint x;
		uint y;
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
		uint8 button;
		int x;
		int y;
	};
	struct MouseWheelEvent {
		int x;
		int y;
	};

	Type type;
	union {
		WindowEvent window;
		WindowResizeEvent windowSize;
		WindowMoveEvent windowMove;
		KeyEvent key;
		TextEvent text;
		MouseMoveEvent mousePos;
		MouseButtonEvent mouseButton;
		MouseWheelEvent mouseWheel;
	};

	static auto isWindowEvent(Type type)->bool;
};

} // namespace KidClone
