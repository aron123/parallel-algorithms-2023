#pragma once
#include "MedianFilter.h"

class SerialMedianFilter : public MedianFilter
{
public:
	SerialMedianFilter(const BMPFile& input, int kernelSize);

	void filter(BMPFile& output) override;

private:
	const BMPFile& m_input;
	BMPFile m_output;
	int m_kernelSize;
};

