#include "SerialMedianFilter.h"

SerialMedianFilter::SerialMedianFilter(const BMPFile& input, int kernelSize)
	: m_input(input), m_output(BMPFile(input)), m_kernelSize(kernelSize)
{
}

void SerialMedianFilter::filter(BMPFile& output)
{
	// TODO: implement
	output = m_output;
}

