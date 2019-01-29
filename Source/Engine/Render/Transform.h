#pragma once
#include <Source/Common.h>

namespace KidClone {

class Transform {
public:
	Transform();
	Transform(std::array<double, 9> matrix3x3);

	auto getMatrix() const->const double*;
	auto getInverse() const->Transform;
	auto transformPoint(double x, double y) const->Vector2d;
	auto transformPoint(const Vector2d& point) const->Vector2d;
	auto transformRect(const FloatRect& rectangle) const->FloatRect;
	auto combine(const Transform& transform)->Transform&;
	auto translate(double x, double y)->Transform&;
	auto translate(const Vector2d& offset)->Transform&;
	auto rotate(double angle)->Transform&;
	auto rotate(double angle, double centerX, double centerY)->Transform&;
	auto rotate(double angle, const Vector2d& center)->Transform&;
	auto scale(double scaleX, double scaleY)->Transform&;
	auto scale(double scaleX, double scaleY, double centerX, double centerY)->Transform&;
	auto scale(const Vector2d& factors)->Transform&;
	auto scale(const Vector2d& factors, const Vector2d& center)->Transform&;

private:
	std::array<double, 16> m_matrix;
};

auto operator *(const Transform& left, const Transform& right)->Transform;
auto operator *=(Transform& left, const Transform& right)->Transform&;
auto operator *(const Transform& left, const Vector2d& right)->Vector2d;

}
