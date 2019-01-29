#include <Source/pch.h>
#include "Transform.h"
#define USE_MATH_DEFINES
#include <math.h>

namespace KidClone {

Transform::Transform() :
	m_matrix({
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	})
{
}

Transform::Transform(std::array<double, 9> matrix) :
	m_matrix({
		matrix[0], matrix[3], 0.0, matrix[6],
		matrix[1], matrix[4], 0.0, matrix[7],
		0.0, 0.0, 1.0, 0.0,
		matrix[2], matrix[5], 0.0, matrix[8]
	})
{
}

auto Transform::getMatrix() const->const double*
{
	return m_matrix.data();
}

auto Transform::getInverse() const->Transform
{
	auto det = m_matrix[0] * (m_matrix[15] * m_matrix[5] - m_matrix[7] * m_matrix[13]) -
				m_matrix[1] * (m_matrix[15] * m_matrix[4] - m_matrix[7] * m_matrix[12]) +
				m_matrix[3] * (m_matrix[13] * m_matrix[4] - m_matrix[5] * m_matrix[12]);
	if (det) {
		return Transform({
			 (m_matrix[15] * m_matrix[5] - m_matrix[7] * m_matrix[13]) / det,
			-(m_matrix[15] * m_matrix[4] - m_matrix[7] * m_matrix[12]) / det,
			 (m_matrix[13] * m_matrix[4] - m_matrix[5] * m_matrix[12]) / det,
			-(m_matrix[15] * m_matrix[1] - m_matrix[3] * m_matrix[13]) / det,
			 (m_matrix[15] * m_matrix[0] - m_matrix[3] * m_matrix[12]) / det,
			-(m_matrix[13] * m_matrix[0] - m_matrix[1] * m_matrix[12]) / det,
			 (m_matrix[7] * m_matrix[1] - m_matrix[3] * m_matrix[5]) / det,
			-(m_matrix[7] * m_matrix[0] - m_matrix[3] * m_matrix[4]) / det,
			 (m_matrix[5] * m_matrix[0] - m_matrix[1] * m_matrix[4]) / det
		});
	}
	return Transform{};
}

auto Transform::transformPoint(double x, double y) const->Vector2d
{
	return Vector2d{
		m_matrix[0] * x + m_matrix[4] * y + m_matrix[12],
		m_matrix[1] * x + m_matrix[5] * y + m_matrix[13]
	};
}

auto Transform::transformPoint(const Vector2d& point) const->Vector2d
{
	return transformPoint(point.x, point.y);
}

auto Transform::transformRect(const FloatRect& rectangle) const->FloatRect
{
	// Transform the 4 corners of the rectangle
	const auto points = std::array<Vector2d, 4>{
		transformPoint(rectangle.left, rectangle.top),
		transformPoint(rectangle.left, rectangle.top + rectangle.height),
		transformPoint(rectangle.left + rectangle.width, rectangle.top),
		transformPoint(rectangle.left + rectangle.width, rectangle.top + rectangle.height)
	};

	// Compute the bounding rectangle of the transformed points
	auto left = points[0].x;
	auto top = points[0].y;
	auto right = points[0].x;
	auto bottom = points[0].y;
	for (int i = 1; i < 4; ++i) {
		if (points[i].x < left)   left = points[i].x;
		else if (points[i].x > right)  right = points[i].x;
		if (points[i].y < top)    top = points[i].y;
		else if (points[i].y > bottom) bottom = points[i].y;
	}
	return FloatRect(left, top, right - left, bottom - top);
}

auto Transform::combine(const Transform& transform)->Transform&
{
	const auto& a = m_matrix;
	const auto& b = transform.m_matrix;

	*this = Transform({
		a[0] * b[0] + a[4] * b[1] + a[12] * b[3],
		a[0] * b[4] + a[4] * b[5] + a[12] * b[7],
		a[0] * b[12] + a[4] * b[13] + a[12] * b[15],
		a[1] * b[0] + a[5] * b[1] + a[13] * b[3],
		a[1] * b[4] + a[5] * b[5] + a[13] * b[7],
		a[1] * b[12] + a[5] * b[13] + a[13] * b[15],
		a[3] * b[0] + a[7] * b[1] + a[15] * b[3],
		a[3] * b[4] + a[7] * b[5] + a[15] * b[7],
		a[3] * b[12] + a[7] * b[13] + a[15] * b[15]
	});
	return *this;
}

auto Transform::translate(double x, double y)->Transform&
{
	Transform translation({
		1, 0, x,
		0, 1, y,
		0, 0, 1
	});
	return combine(translation);
}

auto Transform::translate(const Vector2d& offset)->Transform&
{
	return translate(offset.x, offset.y);
}

auto Transform::rotate(double angle)->Transform&
{
	auto rad = angle * pi<double> / 180.0;
	auto cos = std::cos(rad);
	auto sin = std::sin(rad);

	Transform rotation({
		cos, -sin, 0,
		sin, cos, 0,
		0, 0, 1
	});
	return combine(rotation);
}

auto Transform::rotate(double angle, double centerX, double centerY)->Transform&
{
	auto rad = angle * pi<double> / 180.f;
	auto cos = std::cos(rad);
	auto sin = std::sin(rad);

	Transform rotation({
		cos, -sin, centerX * (1 - cos) + centerY * sin,
		sin, cos, centerY * (1 - cos) - centerX * sin,
		0, 0, 1
	});
	return combine(rotation);
}

auto Transform::rotate(double angle, const Vector2d& center)->Transform&
{
	return rotate(angle, center.x, center.y);
}

auto Transform::scale(double scaleX, double scaleY)->Transform&
{
	Transform scaling({
		scaleX, 0, 0,
		0, scaleY, 0,
		0, 0, 1
	});
	return combine(scaling);
}

auto Transform::scale(double scaleX, double scaleY, double centerX, double centerY)->Transform&
{
	Transform scaling({
		scaleX, 0, centerX * (1 - scaleX),
		0, scaleY, centerY * (1 - scaleY),
		0, 0, 1
	});
	return combine(scaling);
}

auto Transform::scale(const Vector2d& factors)->Transform&
{
	return scale(factors.x, factors.y);
}

auto Transform::scale(const Vector2d& factors, const Vector2d& center)->Transform&
{
	return scale(factors.x, factors.y, center.x, center.y);
}

auto operator *(const Transform& left, const Transform& right)->Transform
{
	return Transform(left).combine(right);
}

auto operator *=(Transform& left, const Transform& right)->Transform&
{
	return left.combine(right);
}

auto operator *(const Transform& left, const Vector2d& right)->Vector2d
{
	return left.transformPoint(right);
}

} // namespace KidClone
