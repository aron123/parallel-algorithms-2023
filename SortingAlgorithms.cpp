#include "SortingAlgorithms.h"

#include <algorithm>
#include <cmath>

void SortingAlgorithms::bucketSort(std::vector<std::byte>& vector)
{
	const auto n = vector.size();
	const int M = static_cast<int>(*std::ranges::max_element(vector)) + 1;

	std::vector<std::vector<std::byte>> buckets(n);

	for (size_t i = 0; i < n; ++i)
	{
		const int bucketIndex = static_cast<int>(std::floor(static_cast<float>(n) * static_cast<float>(vector[i]) / static_cast<float>(M)));
		buckets[bucketIndex].push_back(vector[i]);
	}

	for (auto& bucket : buckets)
	{
		std::ranges::sort(bucket);
	}

	int index = 0;
	for (auto& bucket : buckets)
	{
		for (const auto value : bucket)
		{
			vector[index++] = value;
		}
	}
}

void SortingAlgorithms::parallelBucketSort(std::vector<std::byte>& vector)
{
	const auto n = static_cast<int64_t>(vector.size());
	const int M = static_cast<int>(*std::ranges::max_element(vector)) + 1;

	std::vector<std::vector<std::byte>> buckets(n);

#pragma omp parallel for  // NOLINT(clang-diagnostic-source-uses-openmp)
	for (int64_t i = 0; i < n; ++i)
	{
		const int bucketIndex = static_cast<int>(std::floor(static_cast<float>(n) * static_cast<float>(vector[i]) / static_cast<float>(M)));
#pragma omp critical
		buckets[bucketIndex].push_back(vector[i]);
	}

#pragma omp parallel for
	for (int64_t i = 0; i < n; ++i) // NOLINT(modernize-loop-convert)
	{  
		std::ranges::sort(buckets[i]);
	}

	int index = 0;
#pragma omp parallel for
	for (int64_t i = 0; i < n; ++i)  // NOLINT(modernize-loop-convert)
	{
		for (const auto value : buckets[i])
		{
			vector[index++] = value;
		}
	}
}

size_t SortingAlgorithms::partition(std::vector<std::byte>& vec, size_t low, size_t high) {
	const auto pivot = vec[high];
	size_t i = low - 1;

	for (size_t j = low; j < high; ++j)
	{
		if (vec[j] < pivot)
		{
			++i;
			std::swap(vec[i], vec[j]);
		}
	}

	std::swap(vec[i + 1], vec[high]);
	return i + 1;
}

void SortingAlgorithms::quickSortWith(std::vector<std::byte>& vec, size_t low, size_t high) {
	if (low < high)
	{
		const size_t pivotIndex = partition(vec, low, high);

		if (pivotIndex > 0)
		{
			quickSortWith(vec, low, pivotIndex - 1);
		}

		quickSortWith(vec, pivotIndex + 1, high);
	}
}

void SortingAlgorithms::quickSort(std::vector<std::byte>& vector)
{
	if (!vector.empty())
	{
		quickSortWith(vector, 0, vector.size() - 1);
	}
}

int64_t SortingAlgorithms::parallelPartition(std::vector<std::byte>& vec, int64_t low, int64_t high) {
	const auto pivot = vec[high];
	auto i = low - 1;

#pragma omp parallel for
	for (int64_t j = low; j < high; ++j)
	{
		if (vec[j] < pivot)
		{
#pragma omp critical
			{
				++i;
				std::swap(vec[i], vec[j]);
			}
		}
	}

	std::swap(vec[i + 1], vec[high]);
	return i + 1;
}

void SortingAlgorithms::parallelQuickSortWith(std::vector<std::byte>& vec, int64_t low, int64_t high) {
	if (low < high)
	{
		const auto pivotIndex = parallelPartition(vec, low, high);

#pragma omp parallel sections
		{
#pragma omp section
			{
				if (pivotIndex > 0)
				{
					parallelQuickSortWith(vec, low, pivotIndex - 1);
				}
			}

#pragma omp section
			{
				parallelQuickSortWith(vec, pivotIndex + 1, high);
			}
		}
	}
}

void SortingAlgorithms::parallelQuickSort(std::vector<std::byte>& vector)
{
	if (!vector.empty())
	{
#pragma omp parallel
		{
#pragma omp single nowait
			parallelQuickSortWith(vector, 0, static_cast<int64_t>(vector.size() - 1));
		}
	}
}