#include <Source/pch.h>
#include <Source/Common.h>
#include <Source/Engine/Engine.h>
#include <Source/Engine/Window.h>
#include <Source/Helper/NoCopy.h>
#include <exception>
#include <SDL.h>

#if defined(KIDCLONE_USING_SDL)
	#include <Source/Engine/SDL/EventsImplSDL.h>
#endif

namespace KidClone {

Engine* engine = nullptr;

Engine::Engine()
{
	if (engine || SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		throw new std::runtime_error("Initialization failure");
	}
	engine = this;
}

Engine::~Engine()
{
	SDL_Quit();
	engine = nullptr;
}

auto Engine::get()->Engine*
{
	return engine;
}

auto Engine::run(function<bool()> fn)->void
{
	while (true) {
		EngineEvent event;
		while (EventsImpl::waitEvent(event, 1000 / 60)) {
			if (EngineEvent::isWindowEvent(event.type)) {
				// skip if the window instance has already gone so we don't call event listeners using it
				if (!event.window.window)
					continue;
				auto& window = *event.window.window;
				switch (event.type) {
				case EngineEvent::WindowShow:
					OnWindowShow(window);
					window.OnShow();
					break;
				case EngineEvent::WindowHide:
					OnWindowHide(window);
					window.OnHide();
					break;
				case EngineEvent::WindowGainFocus:
					OnWindowGainFocus(window);
					window.OnGainFocus();
					break;
				case EngineEvent::WindowLoseFocus:
					OnWindowLoseFocus(window);
					window.OnLoseFocus();
					break;
				case EngineEvent::WindowMouseEnter:
					OnWindowMouseEnter(window);
					window.OnMouseEnter();
					break;
				case EngineEvent::WindowMouseLeave:
					OnWindowMouseLeave(window);
					window.OnMouseLeave();
					break;
				case EngineEvent::WindowResize:
					OnWindowResize(window, event.windowSize.width, event.windowSize.height);
					window.OnResize(event.windowSize.width, event.windowSize.height);
					break;
				case EngineEvent::WindowClose:
					OnWindowClose(window);
					window.OnClose();
					break;
				}
			}
			else {
				switch (event.type) {
				case EngineEvent::MouseMove:
					OnMouseMove(event.mousePos.x, event.mousePos.y);
					break;
				case EngineEvent::MouseButtonDown:
					break;
				case EngineEvent::Quit:
					OnQuit();
					break;
				}
			}
		}
		if (!fn()) break;
	}
}

auto Engine::render(RenderTarget& target)->void
{
	target.clear();
	target.display();
}

} // namespace KidClone
