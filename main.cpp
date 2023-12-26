#include <iostream>

#include "Benchmarker.h"
#include "BMPFile.h"
#include "BMPSerializer.h"

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

	const auto benchmarker = new Benchmarker();
	benchmarker->startBenchmark();

	const auto bmp = BMPSerializer::load(std::filesystem::current_path() / parameterValue);

	const auto pixel = bmp->pixel(15, 3);
	std::cout << "First pixel (RGBA): "
		<< std::to_integer<int>(std::get<0>(pixel))
		<< ", " << std::to_integer<int>(std::get<1>(pixel))
		<< ", " << std::to_integer<int>(std::get<2>(pixel))
		<< ", " << std::to_integer<int>(std::get<3>(pixel));

	const auto outputPath = std::filesystem::current_path() / "out" / "out.bmp";
	BMPSerializer::write(outputPath, bmp);

	benchmarker->stopBenchmark();

	std::cout << "\nTime: " << benchmarker->averageTime() << " ms";

	return 0;
}
