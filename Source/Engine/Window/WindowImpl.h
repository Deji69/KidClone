#pragma once
#include <Source/Common.h>
#include <Source/Engine/Config.h>
#include <Source/Engine/Window/VideoMode.h>
#include <Source/Engine/Window/WindowEvent.h>
#include <queue>

#if defined(KIDCLONE_USING_SDL)
struct SDL_Window;
#endif

namespace KidClone {

#if defined(KIDCLONE_USING_SDL)
using WindowHandle = SDL_Window*;
#endif

class WindowImpl {
public:
	static auto create(string_view title, VideoMode mode, uint32 style)->unique_ptr<WindowImpl>;

public:
	virtual ~WindowImpl() = default;

	virtual auto getSystemHandle()->WindowHandle = 0;
	virtual auto getPosition() const->Vector2i = 0;
	virtual auto getSize() const->Vector2u = 0;
	virtual auto getData(string_view name) const->void* = 0;
	virtual auto hasFocus() const->bool = 0;
	virtual auto setPosition(Vector2i)->void = 0;
	virtual auto setSize(Vector2u)->void = 0;
	virtual auto setTitle(string_view)->void = 0;
	virtual auto setIcon(uint width, uint height, const uint8* pixels)->void = 0;
	virtual auto setVisible(bool)->void = 0;
	virtual auto setCursorVisible(bool)->void = 0;
	virtual auto setMouseGrabbed(bool)->void = 0;
	virtual auto setData(string_view name, void* data)->void = 0;
	virtual auto requestFocus()->void = 0;

protected:
	WindowImpl() = default;
};

}
