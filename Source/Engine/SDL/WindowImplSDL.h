#pragma once
#include <SDL.h>
#include <Source/Common.h>
#include <Source/Engine/Config.h>
#include <Source/Engine/Window/VideoMode.h>
#include <Source/Engine/Window/WindowImpl.h>

namespace KidClone {

class WindowImplSDL : public WindowImpl {
public:
	WindowImplSDL(string_view title, VideoMode mode, uint32 style);
	~WindowImplSDL();

	virtual auto getPosition() const->Vector2i override;
	virtual auto getSize() const->Vector2u override;
	virtual auto getData(string_view name) const->void* override;
	virtual auto getSystemHandle()->WindowHandle override;
	virtual auto hasFocus() const->bool override;
	virtual auto setPosition(Vector2i)->void override;
	virtual auto setSize(Vector2u)->void override;
	virtual auto setTitle(string_view)->void override;
	virtual auto setIcon(uint width, uint height, const uint8* pixels)->void override;
	virtual auto setVisible(bool)->void override;
	virtual auto setCursorVisible(bool)->void override;
	virtual auto setMouseGrabbed(bool)->void override;
	virtual auto setData(string_view name, void* data)->void override;
	virtual auto requestFocus()->void override;

private:
	WindowHandle m_handle;
};

}
