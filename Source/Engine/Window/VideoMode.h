#pragma once
#include <Source/Common.h>

namespace KidClone {

class VideoMode {
public:
	VideoMode() = default;
	VideoMode(unsigned int width, unsigned int height, unsigned int bitsPerPixel = 32);

	static VideoMode getDesktopMode();
	static const vector<VideoMode>& getFullscreenModes();

	bool isValid() const;

	bool operator==(const VideoMode& rhs) const;
	bool operator!=(const VideoMode& rhs) const;
	bool operator>(const VideoMode& rhs) const;
	bool operator<(const VideoMode& rhs) const;
	bool operator>=(const VideoMode& rhs) const;
	bool operator<=(const VideoMode& rhs) const;

	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int bitsPerPixel = 0;
};

}
