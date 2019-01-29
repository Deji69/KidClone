#include <Source/pch.h>
#include <algorithm>
#include "VideoMode.h"
#include "VideoModeImpl.h"

namespace KidClone {

VideoMode::VideoMode(unsigned int width, unsigned int height, unsigned int bitsPerPixel) :
	width(width),
	height(height),
	bitsPerPixel(bitsPerPixel)
{
}

VideoMode VideoMode::getDesktopMode()
{
	return VideoModeImpl::getDesktopMode();
}

const vector<VideoMode>& VideoMode::getFullscreenModes()
{
	static vector<VideoMode> modes;
	if (modes.empty()) {
		modes = VideoModeImpl::getFullscreenModes();
		std::sort(modes.begin(), modes.end(), std::greater<VideoMode>());
	}
	return modes;
}

bool VideoMode::isValid() const
{
	auto& modes = getFullscreenModes();
	return std::find(modes.begin(), modes.end(), *this) != modes.end();
}

bool VideoMode::operator==(const VideoMode& rhs) const
{
	return	width == rhs.width &&
			height == rhs.height &&
			bitsPerPixel == rhs.bitsPerPixel;
}

bool VideoMode::operator!=(const VideoMode& rhs) const
{
	return !(*this == rhs);
}

bool VideoMode::operator<(const VideoMode& rhs) const
{
	if (bitsPerPixel == rhs.bitsPerPixel) {
		if (width == rhs.width) {
			return height < rhs.height;
		}
		return width < rhs.width;
	}
	return bitsPerPixel < rhs.bitsPerPixel;
}

bool VideoMode::operator>(const VideoMode& rhs) const
{
	return rhs < *this;
}

bool VideoMode::operator<=(const VideoMode& rhs) const
{
	return !(rhs < *this);
}

bool VideoMode::operator>=(const VideoMode& rhs) const
{
	return !(*this < rhs);
}

}
