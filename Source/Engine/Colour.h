#pragma once
#include <Source/Common.h>

namespace KidClone {

class Colour {
public:
	Colour() = default;
	Colour(uint8 red, uint8 green, uint8 blue, uint8 alpha = 255);
	explicit Colour(uint32 rgba);

	auto toInteger() const->uint32;

public:
	uint8 r = 0;
	uint8 g = 0;
	uint8 b = 0;
	uint8 a = 255;		///< alpha channel
};

bool operator==(const Colour& left, const Colour& right);
bool operator!=(const Colour& left, const Colour& right);

} // namespace KidClone
