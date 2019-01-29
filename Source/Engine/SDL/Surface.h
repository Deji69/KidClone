#pragma once
#include <SDL.h>
#include <Source/Common.h>
#include <Source/Helper/NoCopy.h>

namespace KidClone {

namespace SDL {
	class Surface : NoCopy {
	public:
		Surface(void* pixels, int width, int height, int depth, int pitch, uint Rmask, uint Gmask, uint Bmask, uint Amask);
		Surface(void* pixels, int width, int height, int depth, int pitch = 0, bool alpha = false);
		Surface(SDL_Surface*);				/// < This class takes ownership of the handle
		Surface(Surface&&) noexcept;
		virtual ~Surface();

		auto operator =(Surface&&) noexcept->Surface&;

		auto get() const->SDL_Surface*;


	protected:
		SDL_Surface* m_handle = nullptr;
	};
}

}
