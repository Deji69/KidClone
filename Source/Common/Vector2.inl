#pragma once
#include <Source/Common.h>

template<typename T>
inline Vector2<T>::Vector2(T x, T y) :
	x(x),
	y(y)
{
}

template<typename T>
template<typename U>
inline Vector2<T>::Vector2(const Vector2<U>& vec) :
	x(static_cast<T>(vec.x)),
	y(static_cast<T>(vec.y))
{
}

template<typename T>
inline auto operator -(const Vector2<T>& right)->Vector2<T>
{
	return Vector2<T>(-right.x, -right.y);
}

template<typename T>
inline auto operator +=(Vector2<T>& left, const Vector2<T>& right)->Vector2<T>&
{
	left.x += right.x;
	left.y += right.y;
	return left;
}

template<typename T>
inline auto operator -=(Vector2<T>& left, const Vector2<T>& right)->Vector2<T>&
{
	left.x -= right.x;
	left.y -= right.y;
	return left;
}

template<typename T>
inline auto operator +(const Vector2<T>& left, const Vector2<T>& right)->Vector2<T>
{
	return Vector2<T>(left.x + right.x, left.y + right.y);
}

template<typename T>
inline auto operator -(const Vector2<T>& left, const Vector2<T>& right)->Vector2<T>
{
	return Vector2<T>(left.x - right.x, left.y - right.y);
}

template<typename T>
inline auto operator *(const Vector2<T>& left, T right)->Vector2<T>
{
	return Vector2<T>(left.x * right, left.y * right);
}

template<typename T>
inline auto operator *(T left, const Vector2<T>& right)->Vector2<T>
{
	return Vector2<T>(right.x * left, right.y * left);
}

template<typename T>
inline auto operator *=(Vector2<T>& left, T right)->Vector2<T>&
{
	left.x *= right;
	left.y *= right;
	return left;
}

template<typename T>
inline auto operator /(const Vector2<T>& left, T right)->Vector2<T>
{
	return Vector2<T>(left.x / right, left.y / right);
}

template<typename T>
inline auto operator /=(Vector2<T>& left, T right)->Vector2<T>&
{
	left.x /= right;
	left.y /= right;
	return left;
}

template<typename T>
inline auto operator ==(const Vector2<T>& left, const Vector2<T>& right)->bool
{
	return (left.x == right.x) && (left.y == right.y);
}

template<typename T>
inline auto operator !=(const Vector2<T>& left, const Vector2<T>& right)->bool
{
	return (left.x != right.x) || (left.y != right.y);
}
