#include <iostream>
#include <map>

#include "Benchmarker.h"
#include "BMPFile.h"
#include "BMPSerializer.h"
#include "NoiseGenerator.h"
#include "ParallelMedianFilter.h"
#include "SerialMedianFilter.h"
#include "SortingAlgorithms.h"

constexpr int ARGUMENT_ERROR = -1;
constexpr int RUNTIME_ERROR = -2;

const std::map<std::string, SortingFunction> sortingFunctions = {
	{ "bucket", &SortingAlgorithms::bucketSort },
	{ "bucket-parallel", &SortingAlgorithms::parallelBucketSort },
	{ "quick", &SortingAlgorithms::quickSort },
	{ "quick-parallel", &SortingAlgorithms::parallelQuickSort },
};

SortingFunction determineSortingFunction(const char* name)
{
	if (!sortingFunctions.contains(name))
	{
		const auto errorMessage = std::string("Invalid sorting algorithm ") + "'" + name
			+ "'. Please choose one of 'bucket', 'bucket-parallel', 'quick', 'quick-parallel'.";
		throw std::exception(errorMessage.c_str());
	}

	return sortingFunctions.at(name);
}

std::vector<std::string> splitString(const std::string& input, char delimiter) {
	std::vector<std::string> result;
	std::istringstream stream(input);
	std::string token;

	while (std::getline(stream, token, delimiter)) {
		result.push_back(token);
	}

	return result;
}

std::vector<std::filesystem::path> parseInputFiles(const char* inputFiles)
{
	const auto inputFileStrings = splitString(inputFiles, '|');

	std::vector<std::filesystem::path> filePaths;
	filePaths.reserve(inputFileStrings.size());

	for (const auto& inputFileString : inputFileStrings)
	{
		filePaths.emplace_back(inputFileString);
	}

	return filePaths;
}

void generateNoise(const std::vector<std::filesystem::path>& inputFilePaths, char* const outputFolder, const float noisePercentage)
{
	for (const auto& inputFilePath : inputFilePaths)
	{
		BMPFile inputBMP({});
		BMPSerializer::load(inputFilePath, inputBMP);
		NoiseGenerator::generateNoise(inputBMP, noisePercentage);
		BMPSerializer::write(std::filesystem::path(outputFolder) / inputFilePath.filename(), inputBMP);
	}
}

void medianFilter(const std::vector<std::filesystem::path>& inputFilePaths, const char* outputFolder, int kernelSize,
	const SortingFunction& sortingFunction, int threadCount)
{
	const auto benchmarker = new Benchmarker();

	std::cout << "\nfilename\truntime";

	for (const auto& inputFilePath : inputFilePaths)
	{
		BMPFile inputBMP({});
		BMPSerializer::load(inputFilePath, inputBMP);

		BMPFile outputBMP({});

		MedianFilter* medianFilter;
		if (threadCount == 1)
		{
			medianFilter = new SerialMedianFilter(inputBMP, kernelSize, sortingFunction);
		}
		else
		{
			medianFilter = new ParallelMedianFilter(inputBMP, kernelSize, sortingFunction, threadCount);
		}

		benchmarker->startBenchmark();
		medianFilter->filter(outputBMP);
		benchmarker->stopBenchmark();

		std::cout << "\n" << inputFilePath << "\t" << benchmarker->lastTime() << " ms";

		BMPSerializer::write(std::filesystem::path(outputFolder) / inputFilePath.filename(), outputBMP);
	}

	std::cout << "\navg\t" << benchmarker->averageTime() << " ms";
}

bool areEqual(const char* a, const char* b)
{
	return strcmp(a, b) == 0;
}

void printHelp(const char* message)
{
	std::cout << message;
	std::cout << "\nparallel.exe generate-noise <percentage> <input-files> <output-folder>";
	std::cout << "\nparallel.exe median-filter <kernel-size> <sorting-function> <thread-count> <input-files> <output-folder>";
}

int main(int argc, char* argv[])
{
	if (argc < 2 || (!areEqual(argv[1], "median-filter") && !areEqual(argv[1], "generate-noise")))
	{
		printHelp("\nInvalid parameters are given. Usage options:");
		return ARGUMENT_ERROR;
	}

	const auto command = argv[1];

	if (areEqual(command, "generate-noise") && argc < 5)
	{
		printHelp("\nToo few arguments for command 'generate-noise'.");
		return ARGUMENT_ERROR;
	}

	if (areEqual(command, "median-filter") && argc < 7)
	{
		printHelp("\nToo few arguments for command 'median-filter'.");
		return ARGUMENT_ERROR;
	}

	try
	{
		if (areEqual(command, "generate-noise"))
		{
			const auto noisePercentage = std::stof(argv[2]);
			const auto inputFilePaths = parseInputFiles(argv[3]);
			const auto outputFolder = argv[4];

			generateNoise(inputFilePaths, outputFolder, noisePercentage);
		}

		if (areEqual(command, "median-filter"))
		{
			const auto kernelSize = std::stoi(argv[2]);
			const auto sortingFunction = determineSortingFunction(argv[3]);
			const auto threadCount = static_cast<int>(std::stoul(argv[4]));
			const auto inputFilePaths = parseInputFiles(argv[5]);
			const auto outputFolder = argv[6];
			
			medianFilter(inputFilePaths, outputFolder, kernelSize, sortingFunction, threadCount);
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "\nERROR: " << e.what();
		return RUNTIME_ERROR;
	}

	return 0;
}
