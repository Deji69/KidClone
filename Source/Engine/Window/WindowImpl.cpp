#include <Source/pch.h>
#include "WindowImpl.h"

#if defined(KIDCLONE_USING_SDL)
	#include <Source/Engine/SDL/WindowImplSDL.h>
	using WindowImplType = KidClone::WindowImplSDL;
#endif

namespace KidClone {

auto WindowImpl::create(string_view title, VideoMode mode, uint32 style)->unique_ptr<WindowImpl>
{
	return std::make_unique<WindowImplType>(title, mode, style);
}

} // namespace KidClone
