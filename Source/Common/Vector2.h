#pragma once

namespace KidClone {

using uint = unsigned int;

template<typename T>
class Vector2 {
public:
	/**
	 * Default constructor.
	 *
	 * Creates a Vector2(0, 0)
	 */
	Vector2() = default;

	/**
	 * Construct vector from coords.
	 *
	 * @param  x X coordinate
	 * @param  y Y coordinate
	 */
	Vector2(T x, T y);

	/**
	 * Construct vector from another vector with static cast conversion.
	 *
	 * @param  vec Vector to convert
	 */
	template<typename U>
	explicit Vector2(const Vector2<U>& vec);

	T x;		/// < X coordinate
	T y;		/// < Y coordinate
};

using Vector2i = Vector2<int>;
using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;
using Vector2u = Vector2<uint>;

template<typename T>
Vector2<T> operator -(const Vector2<T>& right);

template<typename T>
Vector2<T>& operator +=(Vector2<T>& left, const Vector2<T>& right);

template<typename T>
Vector2<T>& operator -=(Vector2<T>& left, const Vector2<T>& right);

template<typename T>
Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right);

template<typename T>
Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right);

template<typename T>
Vector2<T> operator *(const Vector2<T>& left, T right);

template<typename T>
Vector2<T> operator *(T left, const Vector2<T>& right);

template<typename T>
Vector2<T>& operator *=(Vector2<T>& left, T right);

template<typename T>
Vector2<T> operator /(const Vector2<T>& left, T right);

template<typename T>
Vector2<T>& operator /=(Vector2<T>& left, T right);

template<typename T>
bool operator ==(const Vector2<T>& left, const Vector2<T>& right);

template<typename T>
bool operator !=(const Vector2<T>& left, const Vector2<T>& right);

#include "Vector2.inl"

}
