#include <Source/pch.h>
#include <Source/Engine/Window/RenderWindow.h>
#include <Source/Engine/SDL/RendererSDL.h>
#include <SDL.h>

namespace KidClone {

RenderWindow::RenderWindow()
{
	m_onWindowCreate = OnCreate.listen([this]() {
		m_renderer = std::make_unique<RendererSDL>(*this);
	});
	m_onWindowClose = OnClose.listen([this]() {
		m_renderer.reset();
	});
}

RenderWindow::RenderWindow(string_view title, VideoMode mode, uint style) :
	RenderWindow()
{
	create(title, mode, style);
}

auto RenderWindow::getRenderer()->RendererSDL&
{
	assert(m_renderer);
	return *m_renderer;
}

auto RenderWindow::getSize() const->Vector2u
{
	return Window::getSize();
}

auto RenderWindow::setLogicalSize(uint width, uint height)->void
{
	assert(m_renderer);
	m_renderer->setLogicalSize(width, height);
}

auto RenderWindow::clear(Colour colour)->void
{
	assert(m_renderer);
	m_renderer->setDrawColour(colour);
	m_renderer->clear();
}

auto RenderWindow::display()->void
{
	m_renderer->display();
	m_clock.restart();
}

} // namespace KidClone
