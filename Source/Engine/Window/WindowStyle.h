#pragma once

namespace KidClone {
namespace WindowStyle {
	enum Flags {
		None = 0,
		Resizable = 1 << 1,
		Fullscreen = 1 << 2,
		Default = Resizable,
	};
}
} // namespace KidClone
