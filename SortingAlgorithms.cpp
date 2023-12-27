#include "SortingAlgorithms.h"

#include <algorithm>
#include <cmath>

void SortingAlgorithms::bucketSort(std::vector<std::byte>& vector)
{
    const auto n = vector.size();
    const int M = static_cast<int>(*std::ranges::max_element(vector)) + 1;
    
    std::vector<std::vector<std::byte>> buckets(n);
    
    for (size_t i = 0; i < n; ++i) {
	    const int bucketIndex = static_cast<int>(std::floor(static_cast<float>(n) * static_cast<float>(vector[i]) / static_cast<float>(M)));
        buckets[bucketIndex].push_back(vector[i]);
    }
    
    for (auto& bucket : buckets) {
        std::ranges::sort(bucket);
    }
    
    int index = 0;
    for (auto& bucket : buckets) {
        for (const auto value : bucket) {
            vector[index++] = value;
        }
    }
}

void SortingAlgorithms::quickSort(std::vector<std::byte>& vector)
{
    if (!vector.empty()) {
        quickSortWith(vector, 0, vector.size() - 1);
    }
}

size_t SortingAlgorithms::partition(std::vector<std::byte>& vec, size_t low, size_t high) {
	const auto pivot = vec[high];
    size_t i = low - 1;

    for (size_t j = low; j < high; ++j) {
        if (vec[j] < pivot) {
            ++i;
            std::swap(vec[i], vec[j]);
        }
    }

    std::swap(vec[i + 1], vec[high]);
    return i + 1;
}

void SortingAlgorithms::quickSortWith(std::vector<std::byte>& vec, size_t low, size_t high) {
    if (low < high) {
	    const size_t pivotIndex = partition(vec, low, high);

        if (pivotIndex > 0) {
            quickSortWith(vec, low, pivotIndex - 1);
        }

        quickSortWith(vec, pivotIndex + 1, high);
    }
}
