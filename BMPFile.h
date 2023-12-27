#pragma once
#include <filesystem>
#include <vector>

struct RGBAColor
{
	std::byte r;
	std::byte g;
	std::byte b;
	std::byte a;
};

class BMPFile
{
public:
	BMPFile(const std::vector<std::byte>& data);
	BMPFile(const BMPFile& bmp) = default;

	void setData(const std::vector<std::byte>& data);
	void setPixel(size_t column, size_t row, const RGBAColor& color);

	[[nodiscard]] const std::vector<std::byte>& data() const;
	[[nodiscard]] const std::byte* rawData() const;
	[[nodiscard]] const std::byte* rawData(size_t offset) const;
	
	[[nodiscard]] uint32_t bitDepth() const;
	[[nodiscard]] uint32_t width() const;
	[[nodiscard]] uint32_t height() const;
	[[nodiscard]] RGBAColor pixel(size_t column, size_t row) const;

private:
	std::filesystem::path m_filePath;
	std::vector<std::byte> m_data;

	uint32_t m_pixelArrayOffset = 0;
	uint32_t m_imageWidth = 0;
	uint32_t m_imageHeight = 0;
	uint32_t m_bitDepth = 0;
	uint32_t m_rowPaddingBits = 0;

	void parseData();

	static uint32_t packed4(const std::byte* bytes);
	static uint32_t packed2(const std::byte* bytes);
};

