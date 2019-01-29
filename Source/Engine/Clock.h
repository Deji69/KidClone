#pragma once
#include <Source/Common.h>

namespace KidClone {

using Hours = chrono::hours;
using Minutes = chrono::minutes;
using Seconds = chrono::seconds;
using Milliseconds = chrono::milliseconds;
using Microseconds = chrono::microseconds;
using SystemClock = chrono::system_clock;
using HighResClock = chrono::high_resolution_clock;
using SystemClockTime = SystemClock::time_point;
using HighResClockTime = HighResClock::time_point;
using HighResClockDuration = HighResClock::duration;
using chrono::duration_cast;

class Clock {
public:
	Clock();

	auto getElapsedTime()->HighResClockDuration;
	auto restart()->HighResClockDuration;

private:
	HighResClockTime m_startTime;
};

} // namespace KidClone
