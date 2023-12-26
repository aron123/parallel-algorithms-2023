#pragma once
#include "BMPFile.h"

class MedianFilter
{
public:
	virtual ~MedianFilter() = default;
	virtual void filter(BMPFile& output) = 0;
};
