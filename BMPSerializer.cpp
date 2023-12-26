#include "BMPSerializer.h"

#include <fstream>

BMPFile* BMPSerializer::load(const std::filesystem::path& filePath)
{
	const auto size = file_size(filePath);
	if (size == 0) {
		return nullptr;
	}

	std::vector<std::byte> data(size);

	std::ifstream inputFile(filePath, std::ios_base::binary);

	inputFile.read(reinterpret_cast<char*>(data.data()), size);
	inputFile.close();

	return new BMPFile(data);
}

void BMPSerializer::write(const std::filesystem::path& filePath, BMPFile* file)
{
	if (!file || file->data().empty())
	{
		throw std::exception("ERROR: File is empty.");
	}

	std::ofstream outputFile{ filePath, std::ios::binary };

	outputFile.write(reinterpret_cast<char*>(file->rawData()), file->data().size() * sizeof(std::byte));
	outputFile.close();
}
