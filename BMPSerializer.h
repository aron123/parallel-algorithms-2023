#pragma once

#include "BMPFile.h"

class BMPSerializer
{
public:
	static void load(const std::filesystem::path& filePath, BMPFile& bmpFile);
	static void write(const std::filesystem::path& filePath, const BMPFile& bmpFile);
};

