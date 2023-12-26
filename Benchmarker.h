#pragma once
#include <chrono>
#include <vector>

class Benchmarker
{
public:
	Benchmarker() = default;

	void startBenchmark();
	void stopBenchmark();

	const std::vector<long long>& times();
	float averageTime();

private:
	std::optional<std::chrono::time_point<std::chrono::steady_clock>> m_currentStartTime = {};
	std::vector<long long> m_benchmarks;
};

