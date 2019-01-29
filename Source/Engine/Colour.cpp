#include <Source/pch.h>
#include <Source/Engine/Colour.h>
#include <Source/Common.h>

namespace KidClone {

Colour::Colour(uint8 red, uint8 green, uint8 blue, uint8 alpha) :
	r(red), g(green), b(blue), a(alpha)
{
}

Colour::Colour(uint32 rgba) :
	r((rgba & 0xFF000000) >> 24),
	g((rgba & 0xFF0000) >> 16),
	b((rgba & 0xFF00) >> 8),
	a((rgba & 0xFF))
{
}

auto Colour::toInteger() const->uint32
{
	return (r << 24) | (g << 16) | (b << 8) | a;
}

bool operator==(const Colour& left, const Colour& right)
{
	return left.a == right.a &&
		left.b == right.b &&
		left.g == right.g &&
		left.r == right.r;
}

bool operator!=(const Colour& left, const Colour& right)
{
	return !(left == right);
}

} // namespace KidClone
