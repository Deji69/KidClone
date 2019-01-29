#pragma once
#include <Source/Common.h>
#include "VideoMode.h"

namespace KidClone {

class VideoModeImpl {
public:
	/**
	 * Get the list of all the supported fullscreen video modes
	 *
	 * @return Array filled with the fullscreen video modes
	 */
	static auto getFullscreenModes()->vector<VideoMode>;

	/**
	 * Get the current desktop video mode
	 *
	 * @return Current desktop video mode
	 */
	static auto getDesktopMode()->VideoMode;

};

}
