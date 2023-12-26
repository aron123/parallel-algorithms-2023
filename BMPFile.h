#pragma once
#include <filesystem>
#include <vector>

using RGBAColor = std::tuple<std::byte, std::byte, std::byte, std::byte>;

class BMPFile
{
public:
	BMPFile(std::vector<std::byte> data);

	[[nodiscard]] const std::vector<std::byte>& data();
	[[nodiscard]] std::byte* rawData();
	[[nodiscard]] std::byte* rawData(size_t offset);

	[[nodiscard]] std::vector<std::byte> header() const;
	[[nodiscard]] uint32_t bitDepth() const;
	[[nodiscard]] uint32_t width() const;
	[[nodiscard]] uint32_t height() const;
	[[nodiscard]] RGBAColor pixel(int column, int row) const;

private:
	std::filesystem::path m_filePath;
	std::vector<std::byte> m_data;

	uint32_t m_pixelArrayOffset = 0;
	uint32_t m_imageWidth = 0;
	uint32_t m_imageHeight = 0;
	uint32_t m_bitDepth = 0;
	uint32_t m_rowPaddingBits = 0;

	static uint32_t packed4(std::byte* bytes);
	static uint32_t packed2(std::byte* bytes);
};

