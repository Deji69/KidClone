#include <Source/pch.h>
#include <Source/Engine/Render/Transformable.h>

namespace KidClone {

auto Transformable::setPosition(double x, double y)->void
{
	m_position.x = x;
	m_position.y = y;
	m_transformNeedsUpdate = true;
	m_inverseTransformNeedsUpdate = true;
}

auto Transformable::setPosition(Vector2d position)->void
{
	setPosition(position.x, position.y);
}

auto Transformable::setRotation(double angle)->void
{
	m_rotation = static_cast<float>(std::fmod(angle, 360));
	if (m_rotation < 0)
		m_rotation += 360.0;

	m_transformNeedsUpdate = true;
	m_inverseTransformNeedsUpdate = true;
}

auto Transformable::setScale(double factorX, double factorY)->void
{
	m_scale.x = factorX;
	m_scale.y = factorY;
	m_transformNeedsUpdate = true;
	m_inverseTransformNeedsUpdate = true;
}

auto Transformable::setScale(Vector2d factors)->void
{
	setScale(factors.x, factors.y);
}

auto Transformable::setOrigin(double x, double y)->void
{
	m_origin.x = x;
	m_origin.y = y;
	m_transformNeedsUpdate = true;
	m_inverseTransformNeedsUpdate = true;
}

auto Transformable::setOrigin(Vector2d origin)->void
{
	setOrigin(origin.x, origin.y);
}

auto Transformable::getPosition() const->Vector2d
{
	return m_position;
}

auto Transformable::getRotation() const->double
{
	return m_rotation;
}

auto Transformable::getScale() const->Vector2d
{
	return m_scale;
}

auto Transformable::getOrigin() const->Vector2d
{
	return m_origin;
}

auto Transformable::move(double offsetX, double offsetY)->void
{
	setPosition(m_position.x + offsetX, m_position.y + offsetY);
}

auto Transformable::move(Vector2d offset)->void
{
	setPosition(m_position.x + offset.x, m_position.y + offset.y);
}

auto Transformable::rotate(double angle)->void
{
	setRotation(m_rotation + angle);
}

auto Transformable::scale(double factorX, double factorY)->void
{
	setScale(m_scale.x * factorX, m_scale.y * factorY);
}

auto Transformable::scale(Vector2d factor)->void
{
	setScale(m_scale.x * factor.x, m_scale.y * factor.y);
}

auto Transformable::getTransform() const->const Transform&
{
	if (m_transformNeedsUpdate) {
		auto angle = -m_rotation * 3.141592654f / 180.f;
		auto cosine = static_cast<float>(std::cos(angle));
		auto sine = static_cast<float>(std::sin(angle));
		auto sxc = m_scale.x * cosine;
		auto syc = m_scale.y * cosine;
		auto sxs = m_scale.x * sine;
		auto sys = m_scale.y * sine;
		auto tx = -m_origin.x * sxc - m_origin.y * sys + m_position.x;
		auto ty = m_origin.x * sxs - m_origin.y * syc + m_position.y;

		m_transform = Transform({
			sxc, sys, tx,
			-sxs, syc, ty,
			0.f, 0.f, 1.f
		});
		m_transformNeedsUpdate = false;
	}
	return m_transform;
}

auto Transformable::getInverseTransform() const->const Transform&
{
	if (m_inverseTransformNeedsUpdate) {
		m_inverseTransform = getTransform().getInverse();
		m_inverseTransformNeedsUpdate = false;
	}
	return m_inverseTransform;
}

} // namespace KidClone
