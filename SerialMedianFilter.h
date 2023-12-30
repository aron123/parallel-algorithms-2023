#pragma once
#include <functional>

#include "MedianFilter.h"

class SerialMedianFilter : public MedianFilter
{
public:
	SerialMedianFilter(const BMPFile& input, int kernelSize, SortingFunction sortingFunction);

	void filter(BMPFile& output) override;

protected:
	const BMPFile& m_input;
	BMPFile m_output;
	int m_kernelSize;
	SortingFunction m_sort;

	[[nodiscard]] RGBAColor newPixelColor(int32_t globalX, int32_t globalY) const;
	[[nodiscard]] std::byte median(std::vector<std::byte>& vector) const;
};

