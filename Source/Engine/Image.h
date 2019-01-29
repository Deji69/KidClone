#pragma once
#include <vector>
#include <istream>
#include <filesystem>
#include <Source/Common.h>
#include <Source/Engine/Colour.h>

namespace KidClone {

class Image {
public:
	Image() = default;
	~Image() = default;

	auto create(uint width, uint height, Colour colour)->void;
	auto create(uint width, uint height, const uint32* pixels)->void;
	auto clear()->void;
	auto loadFromFile(const fs::path& filepath)->bool;
	auto loadFromMemory(const vector<uint8>& buffer)->bool;
	auto loadFromStream(std::istream& stream)->bool;
	auto applyMask(const Colour& color, uint8 alpha)->void;

	auto setPixel(uint x, uint y, Colour colour)->void;

	auto getSize() const->Vector2u;
	auto getPixel(uint x, uint y) const->Colour;
	auto getPixelsVec() const->const vector<uint32>&;

private:
	Vector2u m_size = {0, 0};	///< image dimensions
	vector<uint32> m_data;		///< image data / pixels
};

} // namespace KidClone
