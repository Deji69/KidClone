#pragma once
#include <Source/Common.h>
#include "EngineError.h"
#include <SDL.h>

namespace KidClone {

class SDLError : public EngineError
{
public:
	SDLError(const char* message) : EngineError(message), error(SDL_GetError())
	{
		SDL_ClearError();
	}
	SDLError(const string& message) : SDLError(message.c_str())
	{ }

	const char* error;
};

}
