#include <Source/pch.h>
#include <Source/Game/Game.h>
#include <Source/Engine/Engine.h>

namespace KidClone {

Game::Game(Engine& engine) : m_engine(engine)
{ }

auto Game::start()->void
{
	m_window.create("Kid Chameleon", VideoMode{640, 480, 32});
	m_window.setLogicalSize(640, 480);
	m_image.loadFromFile(fs::path("assets/SpriteSheets_kid.png"));

	auto onQuit = m_engine.OnQuit.listen([this](){
		m_window.close();
	});
	return m_engine.run(std::bind(&Game::run, this));
}

auto Game::run()->bool
{
	if (m_window.isOpen()) {
		//m_window.draw(m_image);
		m_engine.render(m_window);
		return true;
	}
	return false;
}

} // namespace KidClone
