#include <Source/pch.h>
#include <Source/Common.h>
#include <Source/Game/Game.h>
#include <Source/Engine/Engine.h>
#include <Source/Engine/Window.h>
#include <iostream>
#include <Windows.h>

using namespace KidClone;

int main() {
	try {
		Engine engine;
		Game game(engine);
		game.start();
	}
	catch (const std::exception& ex) {
		string str = "An error occurred: "s + ex.what();
		MessageBoxA(0, str.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);
	}
	return 0;
}
