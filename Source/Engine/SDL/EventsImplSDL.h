#pragma once
#include <Source/Common.h>
#include <Source/Engine/Events/EngineEvent.h>

namespace KidClone {

class EventsImpl {
public:
	static auto waitEvent(EngineEvent&, uint timeout = 0)->bool;
	static auto pollEvent(EngineEvent&)->bool;
};

} // KidClone
