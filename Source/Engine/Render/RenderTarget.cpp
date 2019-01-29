#include <Source/pch.h>
#include "RenderTarget.h"

namespace KidClone {

auto RenderTarget::draw(const Drawable& drawable)->void
{
	drawable.draw(*this);
}

} // namespace KidClone
