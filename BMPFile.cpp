#include "BMPFile.h"

#include <utility>

constexpr auto BMP_HEADER_SIZE = 14;
constexpr auto PIXEL_ARR_OFFSET_OFFSET = 10;
constexpr auto IMG_WIDTH_OFFSET = BMP_HEADER_SIZE + 4;
constexpr auto IMG_HEIGHT_OFFSET = BMP_HEADER_SIZE + 2 * 4;
constexpr auto BIT_DEPTH_OFFSET = BMP_HEADER_SIZE + 3 * 4 + 2;

BMPFile::BMPFile(const std::vector<std::byte>& data)
{
	setData(data);
}

void BMPFile::setData(const std::vector<std::byte>& data)
{
	m_data = data;
	if (!m_data.empty())
	{
		parseData();
	}
}

const std::vector<std::byte>& BMPFile::data() const
{
	return m_data;
}

const std::byte* BMPFile::rawData() const
{
	return m_data.data();
}

const std::byte* BMPFile::rawData(size_t offset) const
{
	return rawData() + offset;
}

uint32_t BMPFile::bitDepth() const
{
	return m_bitDepth;
}

uint32_t BMPFile::width() const
{
	return m_imageWidth;
}

uint32_t BMPFile::height() const
{
	return m_imageHeight;
}

RGBAColor BMPFile::pixel(int column, int row) const
{
	// assume, that lines are stored in a reversed order
	const auto x = column;
	const auto y = (m_imageHeight - 1) - row;
	
	const auto offset = m_pixelArrayOffset + (y * (m_bitDepth * m_imageWidth + m_rowPaddingBits) + x * m_bitDepth) / 8;

	const auto b = m_data.at(offset);
	const auto g = m_data.at(offset + 1);
	const auto r = m_data.at(offset + 2);
	const auto a = m_data.at(offset + 3);
	
	return { r, g, b, a };
}

void BMPFile::parseData()
{
	m_pixelArrayOffset = packed4(rawData(PIXEL_ARR_OFFSET_OFFSET));
	m_imageWidth = packed4(rawData(IMG_WIDTH_OFFSET));
	m_imageHeight = packed4(rawData(IMG_HEIGHT_OFFSET));
	m_bitDepth = packed2(rawData(BIT_DEPTH_OFFSET));

	// row size should be a multiple of 4 bytes
	m_rowPaddingBits = (m_imageWidth * m_bitDepth) % 32;
}

uint32_t BMPFile::packed4(const std::byte* bytes)
{
	// little-endian
	return static_cast<unsigned char>(bytes[3]) << 24 |
		static_cast<unsigned char>(bytes[2]) << 16 |
		static_cast<unsigned char>(bytes[1]) << 8 |
		static_cast<unsigned char>(bytes[0]);
}

uint32_t BMPFile::packed2(const std::byte* bytes)
{
	// little-endian
	return static_cast<unsigned char>(bytes[1]) << 8 |
		static_cast<unsigned char>(bytes[0]);
}