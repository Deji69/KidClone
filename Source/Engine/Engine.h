#pragma once
#include <Source/Common.h>
#include <Source/Engine/Event.h>
#include <Source/Engine/Window.h>
#include <Source/Engine/Render/RenderTarget.h>

namespace KidClone {

class Engine : NoCopy {
public:
	virtual ~Engine();
	Engine();
	Engine(Engine&&) = delete;
	auto operator=(Engine&&)->Engine& = delete;

	auto run(function<bool()> fn)->void;
	auto render(RenderTarget&)->void;

public:
	Event<>
		OnQuit;
	Event<uint, uint>
		OnMouseMove;
	Event<Window&>
		OnWindowShow;
	Event<Window&>
		OnWindowHide;
	Event<Window&>
		OnWindowClose;
	Event<Window&, uint, uint>
		OnWindowResize;
	Event<Window&>
		OnWindowGainFocus;
	Event<Window&>
		OnWindowLoseFocus;
	Event<Window&>
		OnWindowMouseEnter;
	Event<Window&>
		OnWindowMouseLeave;

	static auto get()->Engine*;
};

} // namespace KidClone
