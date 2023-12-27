#include <iostream>

#include "Benchmarker.h"
#include "BMPFile.h"
#include "BMPSerializer.h"
#include "SerialMedianFilter.h"
#include "SortingAlgorithms.h"

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

	try
	{
		BMPFile inputBMP({});
		const auto inputPath = std::filesystem::current_path() / parameterValue;
		BMPSerializer::load(inputPath, inputBMP);

		const auto filter = new SerialMedianFilter(inputBMP, 5, &SortingAlgorithms::quickSort);
		BMPFile outputBMP({});
		filter->filter(outputBMP);

		const auto outputPath = std::filesystem::current_path() / "out" / "out.bmp";
		BMPSerializer::write(outputPath, outputBMP);
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
		return -1;
	}


	benchmarker->stopBenchmark();

	std::cout << "\nTime: " << benchmarker->averageTime() << " ms";

	return 0;
}
