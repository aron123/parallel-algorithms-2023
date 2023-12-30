#pragma once
#include <vector>

class SortingAlgorithms
{
public:
	static void bucketSort(std::vector<std::byte>& vector);
	static void parallelBucketSort(std::vector<std::byte>& vector);

	static void quickSort(std::vector<std::byte>& vector);
	static void parallelQuickSort(std::vector<std::byte>& vector);

private:
	static size_t partition(std::vector<std::byte>& vec, size_t low, size_t high);
	static void quickSortWith(std::vector<std::byte>& vec, size_t low, size_t high);

	static int64_t partition(std::vector<std::byte>& vec, int64_t low, int64_t high);
	static void quickSortWith(std::vector<std::byte>& vec, int64_t low, int64_t high);
};

