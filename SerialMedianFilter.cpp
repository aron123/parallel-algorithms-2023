#include "SerialMedianFilter.h"

SerialMedianFilter::SerialMedianFilter(const BMPFile& input, int kernelSize,
                                       std::function<void(std::vector<std::byte>&)> sortingFunction)
	: m_input(input), m_output(BMPFile(input)), m_kernelSize(kernelSize), m_sort(std::move(sortingFunction))
{
}

void SerialMedianFilter::filter(BMPFile& output)
{
	const auto width = static_cast<int32_t>(m_input.width());
	const auto height = static_cast<int32_t>(m_input.height());

	for(int32_t y = 0; y < height; ++y)
	{
		for (int32_t x = 0; x < width; ++x)
		{
			const auto newColor = newPixelColor(x, y);
			m_output.setPixel(x, y, newColor);
		}
	}

	output = m_output;
}

RGBAColor SerialMedianFilter::newPixelColor(int32_t globalX, int32_t globalY) const
{
	const auto radius = static_cast<int32_t>(floor(m_kernelSize / 2));
	const auto minX = globalX - radius;
	const auto maxX = globalX + radius;
	const auto minY = globalY - radius;
	const auto maxY = globalY + radius;

	auto reds = std::vector<std::byte>();
	auto greens = std::vector<std::byte>();
	auto blues = std::vector<std::byte>();

	for (int localY = minY; localY <= maxY; ++localY)
	{
		for (int localX = minX; localX <= maxX; ++localX)
		{
			const auto rgba = m_input.pixel(localX, localY);
			reds.push_back(rgba.r);
			greens.push_back(rgba.g);
			blues.push_back(rgba.b);
		}
	}

	return {
		median(reds),
		median(greens),
		median(blues),
		std::byte{0}
	};
}

std::byte SerialMedianFilter::median(std::vector<std::byte>& vector) const
{
	m_sort(vector);

	return vector.size() % 2 == 0
		? static_cast<std::byte>(static_cast<uint8_t>(vector.at(vector.size() / 2) ^ vector.at(vector.size() / 2 + 1)) / 2)
		: vector.at(vector.size() / 2);
}
