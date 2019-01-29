#include <Source/pch.h>
#include <Tests/Setup.h>
#include <Source/Engine/Engine.h>
#include <Source/Engine/SDL/RendererSDL.h>
#include <Source/Engine/SDL/TextureSDL.h>
#include <sstream>

class TextureTest : public EngineTest
{ };

TEST_F(TextureTest, CreateTextureSDL) {
	RendererSDL renderer{m_window};
	TextureSDL texture;
	ASSERT_TRUE(texture.create(renderer, 32, 32))
		<< "Failed to create texture: " << testLog.lastLog;
	//Window window("Test", VideoMode{640, 480, 32});
}
