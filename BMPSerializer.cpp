#include "BMPSerializer.h"

#include <fstream>

void BMPSerializer::load(const std::filesystem::path& filePath, BMPFile& bmpFile)
{
	const auto size = file_size(filePath);
	std::vector<std::byte> data(size);

	std::ifstream inputFile(filePath, std::ios_base::binary);
	if (!filePath.has_filename() || !inputFile.good())
	{
		const auto errorMessage = std::string("Input is not exists or is not a file: ") + filePath.filename().string();
		throw std::exception(errorMessage.c_str());
	}

	inputFile.read(reinterpret_cast<char*>(data.data()), static_cast<std::streamsize>(size));
	inputFile.close();

	bmpFile.setData(data);
}

void BMPSerializer::write(const std::filesystem::path& filePath, const BMPFile& file)
{
	if (file.data().empty())
	{
		const auto errorMessage = std::string("File to be saved is empty (path: ") + filePath.string() + ").";
		throw std::exception(errorMessage.c_str());
	}

	std::ofstream outputFile{ filePath, std::ios::binary };

	outputFile.write(reinterpret_cast<const char*>(file.rawData()), file.data().size() * sizeof(std::byte));
	outputFile.close();
}
