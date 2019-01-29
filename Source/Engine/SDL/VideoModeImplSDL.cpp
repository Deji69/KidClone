#include <Source/pch.h>
#include <SDL.h>
#include <Source/Engine/Exception/SDLError.h>
#include <Source/Engine/Window/VideoModeImpl.h>

namespace KidClone {

auto VideoModeImpl::getFullscreenModes()->vector<VideoMode>
{
	auto num = SDL_GetNumDisplayModes(0);
	if (num <= 0) {
		throw new SDLError("Error getting display modes");
	}

	vector<VideoMode> modes;
	SDL_DisplayMode sdl_mode;

	for (auto i = 0; i < num; ++i) {
		if (SDL_GetDisplayMode(0, i, &sdl_mode) != 0) {
			throw new SDLError("Error getting display mode");
		}

		VideoMode mode{static_cast<unsigned int>(sdl_mode.w), static_cast<unsigned int>(sdl_mode.h), SDL_BITSPERPIXEL(sdl_mode.format)};

		// check the mode is not already in the array
		if (std::find(modes.begin(), modes.end(), mode) == modes.end())
			modes.push_back(mode);
	}

	if (modes.empty()) {
		throw new EngineError("No video modes defined");
	}
	return modes;
}

auto VideoModeImpl::getDesktopMode()->VideoMode
{
	SDL_DisplayMode sdl_mode;
	if (SDL_GetCurrentDisplayMode(0, &sdl_mode) != 0) {
		throw new SDLError("Error getting display mode");
	}
	return {static_cast<unsigned int>(sdl_mode.w), static_cast<unsigned int>(sdl_mode.h), SDL_BITSPERPIXEL(sdl_mode.format)};
}

}