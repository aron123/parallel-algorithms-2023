#pragma once
#include "SerialMedianFilter.h"
class ParallelMedianFilter : public SerialMedianFilter
{
public:
	ParallelMedianFilter(const BMPFile& input, int kernelSize, std::function<void(std::vector<std::byte>&)> sortingFunction, int threads = -1);

	void filter(BMPFile& output) override;

private:
	int m_threads;
};

