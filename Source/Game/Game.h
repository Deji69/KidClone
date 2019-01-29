#pragma once
#include <Source/Engine/Engine.h>
#include <Source/Engine/Image.h>
#include <Source/Engine/Window/RenderWindow.h>

namespace KidClone {

class Game {
public:
	Game(Engine&);

	auto start()->void;
	auto run()->bool;

private:
	Engine& m_engine;
	Image m_image;
	RenderWindow m_window;
};

} // namespace KidClone
