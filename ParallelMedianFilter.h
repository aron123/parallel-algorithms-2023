#pragma once
#include "SerialMedianFilter.h"
class ParallelMedianFilter : public SerialMedianFilter
{
public:
	ParallelMedianFilter(const BMPFile& input, int kernelSize, SortingFunction sortingFunction, int threads = 0);

	void filter(BMPFile& output) override;

private:
	int m_threads;
};

