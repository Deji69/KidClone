#pragma once
#include <Source/Common.h>
#include <Source/Engine/Config.h>
#include <Source/Engine/Event.h>
#include <Source/Engine/Render/RenderTarget.h>
#include <Source/Engine/Window/VideoMode.h>
#include <Source/Engine/Window/WindowImpl.h>
#include <Source/Engine/Window/WindowStyle.h>

namespace KidClone {

class Window : NoCopy {
public:
	using Style = WindowStyle::Flags;

public:
	Window() = default;
	Window(string_view title, VideoMode mode, uint style = Style::Default);
	Window(Window&&);
	~Window() = default;

	auto getPosition() const->Vector2i;
	auto getSize() const->Vector2u;
	auto getImpl()->WindowImpl&;
	auto getImpl() const->const WindowImpl&;
	auto getSystemHandle() const->WindowHandle;
	auto isOpen() const->bool;
	auto hasFocus() const->bool;
	auto requestFocus()->void;
	auto setCursorVisible(bool)->void;
	auto setMouseGrabbed(bool)->void;
	auto setPosition(Vector2i)->void;
	auto setSize(Vector2u)->void;
	auto setTitle(string_view)->void;
	auto setVisible(bool)->void;
	auto create(string_view title, VideoMode mode, uint style = Style::Default)->void;
	auto close()->void;

public:
	Event<>				OnCreate;
	Event<>				OnClose;
	Event<>				OnShow;
	Event<>				OnHide;
	Event<uint, uint> 	OnResize;
	Event<>				OnGainFocus;
	Event<>				OnLoseFocus;
	Event<>				OnMouseEnter;
	Event<>				OnMouseLeave;

private:
	auto init()->void;

private:
	unique_ptr<WindowImpl> m_impl;
};

}
