#pragma once
#include <functional>

#include "BMPFile.h"

using SortingFunction = std::function<void(std::vector<std::byte>&)>;

class MedianFilter
{
public:
	virtual ~MedianFilter() = default;
	virtual void filter(BMPFile& output) = 0;
};
