#pragma once
#include <Source/Engine/Render/Transform.h>

namespace KidClone {

class Transformable {
public:
	virtual ~Transformable() = default;
	Transformable() = default;

	auto setPosition(double x, double y)->void;
	auto setPosition(Vector2d)->void;
	auto setRotation(double)->void;
	auto setScale(double factorX, double factorY)->void;
	auto setScale(Vector2d factors)->void;
	auto setOrigin(double x, double y)->void;
	auto setOrigin(Vector2d origin)->void;
	auto getPosition() const->Vector2d;
	auto getRotation() const->double;
	auto getScale() const->Vector2d;
	auto getOrigin() const->Vector2d;
	auto getTransform() const->const Transform&;
	auto getInverseTransform() const->const Transform&;
	auto move(double offsetX, double offsetY)->void;
	auto move(Vector2d offset)->void;
	auto rotate(double angle)->void;
	auto scale(double factorX, double factorY)->void;
	auto scale(Vector2d factor)->void;

private:
	Vector2d m_origin = {0, 0};
	Vector2d m_position = {0, 0};
	double m_rotation = 0;
	Vector2d m_scale = {1, 1};
	mutable Transform m_transform;
	mutable Transform m_inverseTransform;
	mutable bool m_transformNeedsUpdate = true;
	mutable bool m_inverseTransformNeedsUpdate = true;
};

} // namespace KidClone
