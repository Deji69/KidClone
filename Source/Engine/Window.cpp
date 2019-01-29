#include <Source/pch.h>
#include "Config.h"
#include "Window.h"

namespace KidClone {

Window::Window(string_view title, VideoMode mode, uint style)
{
	create(title, mode, style);
}

Window::Window(Window&& other) : m_impl(std::move(other.m_impl))
{
	m_impl->setData("window", this);
}

auto Window::getPosition() const->Vector2i
{
	assert(m_impl);
	return m_impl->getPosition();
}

auto Window::getSize() const->Vector2u
{
	assert(m_impl);
	return m_impl->getSize();
}

auto Window::getImpl()->WindowImpl&
{
	assert(m_impl);
	return *m_impl;
}

auto Window::getImpl() const->const WindowImpl&
{
	assert(m_impl);
	return *m_impl;
}

auto Window::getSystemHandle() const->WindowHandle
{
	return m_impl ? m_impl->getSystemHandle() : nullptr;
}

auto Window::isOpen() const->bool
{
	return !!m_impl;
}

auto Window::hasFocus() const->bool
{
	return m_impl && m_impl->hasFocus();
}

auto Window::requestFocus()->void
{
	assert(m_impl);
	return m_impl->requestFocus();
}

auto Window::setCursorVisible(bool visible)->void
{
	assert(m_impl);
	m_impl->setCursorVisible(visible);
}

auto Window::setMouseGrabbed(bool grab)->void
{
	assert(m_impl);
	m_impl->setMouseGrabbed(grab);
}

auto Window::setPosition(Vector2i pos)->void
{
	assert(m_impl);
	m_impl->setPosition(pos);
}

auto Window::setSize(Vector2u size)->void
{
	assert(m_impl);
	m_impl->setSize(size);
}

auto Window::setTitle(string_view title)->void
{
	assert(m_impl);
	m_impl->setTitle(title);
}

auto Window::setVisible(bool visibility)->void
{
	m_impl->setVisible(visibility);
}

auto Window::create(string_view title, VideoMode mode, uint style)->void
{
	m_impl = WindowImpl::create(title, mode, style);
	m_impl->setData("window", this);
	init();
}

auto Window::close()->void
{
	m_impl.reset();
}

auto Window::init()->void
{
	setVisible(true);
	setCursorVisible(true);
	OnCreate();
}

}
