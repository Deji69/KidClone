#pragma once

namespace KidClone {

class RenderTarget;

class Drawable {
public:
	virtual ~Drawable() = default;

protected:
	friend RenderTarget;

	virtual auto draw(RenderTarget&) const->void = 0;
};

} // namespace KiClone
