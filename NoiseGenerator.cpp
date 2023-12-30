#include "NoiseGenerator.h"

#include <random>

void NoiseGenerator::generateNoise(BMPFile& bmp, float noiseLevel)
{
	if (noiseLevel < 0.0f)
	{
		noiseLevel = 0.0f;
	}

	if (noiseLevel > 1.0f)
	{
		noiseLevel = 1.0f;
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	const std::uniform_real_distribution distribution(0.0f, 1.0f);

	constexpr RGBAColor black{ std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0} };
	constexpr RGBAColor white{ std::byte{255}, std::byte{255}, std::byte{255}, std::byte{255} };

	const auto width = static_cast<int32_t>(bmp.width());
	const auto height = static_cast<int32_t>(bmp.height());

#pragma omp parallel for schedule(static)
	for (int32_t y = 0; y < height; ++y)
	{
#pragma omp parallel for schedule(static)
		for (int32_t x = 0; x < width; ++x)
		{
			if (distribution(gen) < noiseLevel)
			{
				bmp.setPixel(x, y, distribution(gen) < 0.5f ? white : black);
			}
		}
	}
}
