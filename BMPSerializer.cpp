#include "BMPSerializer.h"

#include <fstream>

void BMPSerializer::load(const std::filesystem::path& filePath, BMPFile& bmpFile)
{
	const auto size = file_size(filePath);
	std::vector<std::byte> data(size);

	std::ifstream inputFile(filePath, std::ios_base::binary);

	inputFile.read(reinterpret_cast<char*>(data.data()), size);
	inputFile.close();

	bmpFile.setData(data);
}

void BMPSerializer::write(const std::filesystem::path& filePath, const BMPFile& file)
{
	if (file.data().empty())
	{
		throw std::exception("ERROR: File is empty.");
	}

	std::ofstream outputFile{ filePath, std::ios::binary };

	outputFile.write(reinterpret_cast<const char*>(file.rawData()), file.data().size() * sizeof(std::byte));
	outputFile.close();
}
