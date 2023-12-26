#pragma once

#include "BMPFile.h"

class BMPSerializer
{
public:
	static BMPFile* load(const std::filesystem::path& filePath);
	static void write(const std::filesystem::path& filePath, BMPFile* file);
};

