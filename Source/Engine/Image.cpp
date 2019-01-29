#include <Source/pch.h>
#include "Image.h"
#include "Colour.h"
#include <Source/Common.h>
#include <Source/Common/Logging.h>
#ifdef _MSC_VER
	#define STBI_MSC_SECURE_CRT
#endif
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image/stb_image_write.h>
#include <fstream>

namespace KidClone {

namespace {
	auto loadPixelData(vector<uint32>& vec, uint8* data, int width, int height, int channels) {
		if (width && height && channels == 4) {
			vec.resize(width * height);
			memcpy(vec.data(), data, vec.size() * sizeof(uint32));
			return true;
		}
		else {
			error() << "Failed to load image: invalid pixel data loaded";
		}
		return false;
	};
}

auto Image::create(uint width, uint height, Colour colour)->void
{
	if (width && height) {
		// reserve before assign for exception safety
		m_data.reserve(width * height);
		m_data.assign(width * height, colour.toInteger());
		m_size = {width, height};
	}
	else clear();
}

auto Image::create(uint width, uint height, const uint32* pixels)->void
{
	if (pixels && width && height) {
		// reserve before assign for exception safety
		m_data.reserve(width * height);
		m_data.assign(pixels, pixels + width * height);
		m_size = {width, height};
	}
	else clear();
}

auto Image::clear()->void
{
	m_data.clear();
	m_size = {0, 0};
}

auto Image::loadFromFile(const fs::path& path)->bool
{
	clear();

	std::ifstream file(path);
	if (file.is_open()) {
		auto beg = file.tellg();
		file.seekg(0, std::ios_base::end);
		auto end = file.tellg();
		file.seekg(0, std::ios_base::beg);

		vector<uint8> buffer;
		buffer.reserve(end - beg);
		buffer.assign(std::istreambuf_iterator<char>{file}, std::istreambuf_iterator<char>{});

		file.close();
		return loadFromMemory(buffer);
	}

	error() << "Failed to load image file \"" << path.string() << "\": could not open file";
	return false;
}

auto Image::loadFromMemory(const vector<uint8>& buffer)->bool
{
	int width = 0, height = 0, channels = 0;
	clear();

	if (auto ptr = stbi_load_from_memory(buffer.data(), static_cast<int>(buffer.size()), &width, &height, &channels, STBI_rgb_alpha)) {
		m_size.x = width;
		m_size.y = height;
		auto success = loadPixelData(m_data, ptr, width, height, channels);
		stbi_image_free(ptr);
		return success;
	}

	error() << "Failed to load image: " << stbi_failure_reason();
	return false;
}

auto Image::loadFromStream(std::istream& stream)->bool
{
	int width = 0, height = 0, channels = 0;
	clear();
	
	stbi_io_callbacks cbs = {
		// read
		[](void* user, char* data, int size)->int {
			auto stream = static_cast<std::istream*>(user);
			return static_cast<int>(stream->readsome(data, size));
		},
		// skip
		[](void* user, int size)->void {
			auto stream = static_cast<std::istream*>(user);
			stream->seekg(size, std::ios::cur);
		},
		// eof
		[](void* user)->int {
			auto stream = static_cast<std::istream*>(user);
			return stream->peek() == EOF;
		},
	};

	if (auto ptr = stbi_load_from_callbacks(&cbs, &stream, &width, &height, &channels, STBI_rgb_alpha)) {
		m_size.x = width;
		m_size.y = height;
		auto success = loadPixelData(m_data, ptr, width, height, channels);
		stbi_image_free(ptr);
		return success;
	}

	error() << "Failed to load image stream: " << stbi_failure_reason();
	return false;
}

auto Image::applyMask(const Colour& colour, uint8 alpha)->void
{
	Colour pixelColour;
	for (auto& pixel : m_data) {
		pixelColour = Colour{pixel};
		if (pixelColour == colour) {
			pixelColour.a = alpha;
			pixel = pixelColour.toInteger();
		}
	}
}

auto Image::setPixel(uint x, uint y, Colour colour)->void
{
	auto pixel = &m_data[(x + y * m_size.x) * 4];
	*pixel = colour.toInteger();
}

auto Image::getSize() const->Vector2u
{
	return m_size;
}

auto Image::getPixel(uint x, uint y) const->Colour
{
	return Colour{m_data[(x + y * m_size.x) * 4]};
}

auto Image::getPixelsVec() const->const vector<uint32>&
{
	return m_data;
}

} // namespace KidClone
