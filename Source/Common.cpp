#include <Source/pch.h>
#include <Source/Common.h>
#include <ctime>
#include <iomanip>

namespace KidClone {

auto getTimestamp(const char* format)->string {
	auto t = chrono::system_clock::to_time_t(chrono::system_clock::now());
	std::tm tm;
	localtime_s(&tm, &t);
	stringstream ss;
	ss << std::put_time(&tm, format);
	return ss.str();
}

} // namespace KidClone
