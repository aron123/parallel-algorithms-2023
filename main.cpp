#include <iostream>

#include "BMPFile.h"

constexpr auto COLOR_DEPTH = 32;

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		std::cout << "ERROR: Too few arguments.";
		return -1;
	}

	const std::string parameterName = argv[1];
	const std::string parameterValue = argv[2];

	if (parameterName != "-f")
	{
		std::cout << "ERROR: The only supported parameter is \"-f\".";
		return -1;
	}

	const auto bmp = new BMPFile(std::filesystem::current_path() / parameterValue);
	bmp->load();
	const auto data = bmp->data();

	bmp->setFilePath(std::filesystem::current_path() / "out" / "out.bmp");
	bmp->write();

	return 0;
}
