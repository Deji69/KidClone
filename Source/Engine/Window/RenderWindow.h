#pragma once
#include <Source/Common.h>
#include <Source/Engine/Clock.h>
#include <Source/Engine/Window.h>
#include <Source/Engine/Render/RenderTarget.h>
#include <Source/Engine/SDL/RendererSDL.h>

namespace KidClone {

class RenderWindow : public RenderTarget, public Window {
public:
	RenderWindow();
	RenderWindow(string_view title, VideoMode mode, uint style = Style::Default);

	auto getRenderer()->RendererSDL&;
	auto setLogicalSize(uint width, uint height)->void;

	virtual auto getSize() const->Vector2u override;
	virtual auto clear(Colour color)->void override;
	virtual auto display()->void override;

private:
	decltype(Window::OnCreate)::Listener
		m_onWindowCreate;
	decltype(Window::OnClose)::Listener
		m_onWindowClose;
	unique_ptr<RendererSDL> m_renderer;
	Clock m_clock;
};

} // namespace KidClone
