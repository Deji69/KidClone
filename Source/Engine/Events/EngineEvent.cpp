#include <Source/pch.h>
#include "EngineEvent.h"

namespace KidClone {

auto EngineEvent::isWindowEvent(Type type)->bool
{
	switch (type) {
	case WindowMove:
	case WindowResize:
	case WindowClose:
	case WindowGainFocus:
	case WindowLoseFocus:
	case WindowMouseEnter:
	case WindowMouseLeave:
	case WindowShow:
	case WindowHide:
		return true;
	}
	return false;
}

} // namespace KidClone
