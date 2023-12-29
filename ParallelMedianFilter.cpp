#include "ParallelMedianFilter.h"

#include <omp.h>
#include <utility>

ParallelMedianFilter::ParallelMedianFilter(const BMPFile& input, int kernelSize, std::function<void(std::vector<std::byte>&)> sortingFunction, int threads)
	: SerialMedianFilter(input, kernelSize, std::move(sortingFunction)),
	m_threads(threads)
{}

void ParallelMedianFilter::filter(BMPFile& output)
{
	const auto width = static_cast<int32_t>(m_input.width());
	const auto height = static_cast<int32_t>(m_input.height());

	if (m_threads > 0)
	{
		omp_set_num_threads(m_threads);
	}

#pragma omp parallel for schedule(static)
	for (int32_t y = 0; y < height; ++y)
	{
#pragma omp parallel for schedule(static)
		for (int32_t x = 0; x < width; ++x)
		{
			const auto newColor = newPixelColor(x, y);
			m_output.setPixel(x, y, newColor);
		}
	}

	output = m_output;
}