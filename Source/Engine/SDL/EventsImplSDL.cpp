#include <Source/pch.h>
#include <Source/Engine/SDL/EventsImplSDL.h>
#include <SDL.h>

namespace KidClone {

namespace {

auto translateEvent(SDL_Event& ev, EngineEvent& event) {
	switch (ev.type) {
	case SDL_WINDOWEVENT:
	{
		auto window = SDL_GetWindowFromID(ev.window.windowID);
		event.window.window = window ? reinterpret_cast<Window*>(SDL_GetWindowData(window, "window")) : nullptr;
		switch (ev.window.event) {
		case SDL_WINDOWEVENT_SHOWN:
			event.type = EngineEvent::WindowShow;
			break;
		case SDL_WINDOWEVENT_HIDDEN:
			event.type = EngineEvent::WindowHide;
			break;
		case SDL_WINDOWEVENT_CLOSE:
			event.type = EngineEvent::WindowClose;
			break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			event.type = EngineEvent::WindowGainFocus;
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			event.type = EngineEvent::WindowLoseFocus;
			break;
		case SDL_WINDOWEVENT_ENTER:
			event.type = EngineEvent::WindowMouseEnter;
			break;
		case SDL_WINDOWEVENT_LEAVE:
			event.type = EngineEvent::WindowMouseLeave;
			break;
		case SDL_WINDOWEVENT_MOVED:
			event.type = EngineEvent::WindowMove;
			event.windowMove.window = event.window.window;
			event.windowMove.x = ev.window.data1;
			event.windowMove.y = ev.window.data2;
			break;
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			event.type = EngineEvent::WindowResize;
			event.windowSize.window = event.window.window;
			event.windowSize.width = ev.window.data1;
			event.windowSize.height = ev.window.data2;
			break;
		default:
			return false;
		}
		break;
	}
	case SDL_QUIT:
		event.type = EngineEvent::Quit;
		break;
	case SDL_KEYDOWN:
		event.type = EngineEvent::KeyDown;
		// TODO: finish
		break;
	case SDL_KEYUP:
		event.type = EngineEvent::KeyUp;
		// TODO: finish
		break;
	case SDL_MOUSEMOTION:
		event.type = EngineEvent::MouseMove;
		event.mousePos.x = ev.motion.x;
		event.mousePos.y = ev.motion.y;
		break;
	case SDL_MOUSEBUTTONDOWN:
		event.type = EngineEvent::MouseButtonDown;
		event.mouseButton.button = ev.button.button;
		event.mouseButton.x = ev.button.x;
		event.mouseButton.y = ev.button.y;
		break;
	case SDL_MOUSEBUTTONUP:
		event.type = EngineEvent::MouseButtonUp;
		event.mouseButton.button = ev.button.button;
		event.mouseButton.x = ev.button.x;
		event.mouseButton.y = ev.button.y;
		break;
	case SDL_MOUSEWHEEL:
		event.type = EngineEvent::MouseWheel;
		event.mouseWheel.x = ev.wheel.x;
		event.mouseWheel.y = ev.wheel.y;
		break;
	default:
		return false;
	}
	return true;
}

} // anonymous namespace

auto EventsImpl::waitEvent(EngineEvent& event, uint timeout)->bool
{
	SDL_Event ev;
	bool success = false;
	do {
		success = timeout ? SDL_WaitEventTimeout(&ev, timeout) : SDL_WaitEvent(&ev);
	} while (success && !translateEvent(ev, event));
	return success;
}

auto EventsImpl::pollEvent(EngineEvent& event)->bool
{
	SDL_Event ev;
	bool success = false;
	do {
		success = SDL_PollEvent(&ev);
	} while (success && !translateEvent(ev, event));
	return success;
}

} // namespace KidClone
