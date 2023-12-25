#include "BMPFile.h"

#include <fstream>
#include <utility>

BMPFile::BMPFile(const std::filesystem::path& filePath)
{
	m_filename = filePath.string();
}

void BMPFile::load()
{
	const std::filesystem::path inputFilePath{ m_filename };
	const auto size = file_size(inputFilePath);
	if (size == 0) {
		return;
	}

	m_data.resize(size);

	std::ifstream inputFile(m_filename, std::ios_base::binary);
	inputFile.read(reinterpret_cast<char*>(m_data.data()), size);
	inputFile.close();
}

void BMPFile::setData(std::vector<std::byte> data)
{
	m_data = std::move(data);
}

void BMPFile::setFilePath(const std::filesystem::path& filePath)
{
	m_filename = filePath.string();
}

void BMPFile::write()
{
	if (m_data.empty())
	{
		throw std::exception("ERROR: File is empty.");
	}

	const std::filesystem::path outputFilePath{ m_filename };
	std::ofstream outputFile{ outputFilePath, std::ios::binary };

	outputFile.write(reinterpret_cast<const char*>(m_data.data()), m_data.size() * sizeof(decltype(m_data)::value_type));
	outputFile.close();
}

std::vector<std::byte> BMPFile::data()
{
	if (m_data.empty())
	{
		load();
	}

	return m_data;
}
