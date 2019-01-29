#include <Source/pch.h>
#include <Source/Engine/Clock.h>

namespace KidClone {

Clock::Clock() :
	m_startTime(
		duration_cast<Microseconds>(
			HighResClock::now().time_since_epoch()
		)
	)
{ }

auto Clock::getElapsedTime()->HighResClockDuration
{
	return HighResClock::now() - m_startTime;
}

auto Clock::restart()->HighResClockDuration
{
	auto now = HighResClock::now();
	auto elapsed = now - m_startTime;
	m_startTime = now;
	return elapsed;
}

} // namespace KidClone
