#pragma once
#include <string>
#include <filesystem>
#include <vector>

class BMPFile
{
public:
	BMPFile(const std::filesystem::path& filePath);

	void load();
	[[nodiscard]] std::vector<std::byte> data();

	void setData(std::vector<std::byte> data);
	void setFilePath(const std::filesystem::path& filePath);
	void write();

private:
	std::string m_filename;
	std::vector<std::byte> m_data{0};
};

