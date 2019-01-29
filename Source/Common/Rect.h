#pragma once
#include <Source/Common/Vector2.h>

namespace KidClone {

template<typename T>
class Rect {
public:
	Rect() = default;

	Rect(T left, T top, T width, T height) : left(left), top(top), width(width), height(height)
	{ }

	Rect(const Vector2<T>& position, const Vector2<T>& size) : left(position.x), top(position.y), width(size.x), height(size.y)
	{ }

	template<typename U>
	explicit Rect(const Rect<U>& rectangle) :
		left(static_cast<T>(rectangle.left)),
		top(static_cast<T>(rectangle.top)),
		width(static_cast<T>(rectangle.width)),
		height(static_cast<T>(rectangle.height))
	{ }

	auto contains(T x, T y) const->bool
	{
		auto minX = std::min(left, static_cast<T>(left + width));
		auto maxX = std::max(left, static_cast<T>(left + width));
		auto minY = std::min(top, static_cast<T>(top + height));
		auto maxY = std::max(top, static_cast<T>(top + height));
		return (x >= minX) && (x < maxX) && (y >= minY) && (y < maxY);
	}

	auto contains(const Vector2<T>& point) const->bool
	{
		return contains(point.x, point.y);
	}

	auto intersects(const Rect<T>& rectangle) const->bool
	{
		Rect<T> intersection;
		return intersects(rectangle, intersection);
	}

	auto intersects(const Rect<T>& rectangle, Rect<T>& intersection) const->bool
	{
		auto r1MinX = std::min(left, static_cast<T>(left + width));
		auto r1MaxX = std::max(left, static_cast<T>(left + width));
		auto r1MinY = std::min(top, static_cast<T>(top + height));
		auto r1MaxY = std::max(top, static_cast<T>(top + height));
		auto r2MinX = std::min(rectangle.left, static_cast<T>(rectangle.left + rectangle.width));
		auto r2MaxX = std::max(rectangle.left, static_cast<T>(rectangle.left + rectangle.width));
		auto r2MinY = std::min(rectangle.top, static_cast<T>(rectangle.top + rectangle.height));
		auto r2MaxY = std::max(rectangle.top, static_cast<T>(rectangle.top + rectangle.height));
		auto interLeft = std::max(r1MinX, r2MinX);
		auto interTop = std::max(r1MinY, r2MinY);
		auto interRight = std::min(r1MaxX, r2MaxX);
		auto interBottom = std::min(r1MaxY, r2MaxY);
		if ((interLeft < interRight) && (interTop < interBottom)) {
			intersection = Rect<T>(interLeft, interTop, interRight - interLeft, interBottom - interTop);
			return true;
		}
		intersection = Rect<T>(0, 0, 0, 0);
		return false;
	}

	T left = 0;
	T top = 0;
	T width = 0;
	T height = 0;
};

template<typename T>
inline auto operator==(const Rect<T>& left, const Rect<T>& right)->bool
{
	return (left.left == right.left) && (left.width == right.width) &&
		(left.top == right.top) && (left.height == right.height);
}

template <typename T>
inline auto operator !=(const Rect<T>& left, const Rect<T>& right)->bool
{
	return !(left == right);
}

using IntRect = Rect<int>;
using FloatRect = Rect<double>;

}
