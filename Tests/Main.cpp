#include <Source/pch.h>
#include <Source/Common.h>
#include <Source/Game/Game.h>
#include <Source/Engine/Engine.h>
#include <Source/Engine/Window.h>
#include <Tests/Setup.h>
#include <Windows.h>
#include <iostream>

using namespace KidClone;

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	debug().setLogger(testLog);
	info().setLogger(testLog);
	warning().setLogger(testLog);
	error().setLogger(testLog);
	return RUN_ALL_TESTS();
}
