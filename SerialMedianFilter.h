#pragma once
#include "MedianFilter.h"
class SerialMedianFilter : public MedianFilter
{
public:
	SerialMedianFilter(const BMPFile& input, int kernelSize);

	void filter(BMPFile& output) override;

private:
	//BMPFile& m_input;
	//int m_kernelSize;
};

