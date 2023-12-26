#include "Benchmarker.h"

#include <numeric>

void Benchmarker::startBenchmark()
{
    if (m_currentStartTime.has_value())
    {
        stopBenchmark();
    }

    m_currentStartTime = std::chrono::steady_clock::now();
}

void Benchmarker::stopBenchmark()
{
    if (!m_currentStartTime.has_value())
    {
        return;
    }

    const auto endTime = std::chrono::steady_clock::now();
    const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_currentStartTime.value());

    m_benchmarks.push_back(elapsed.count());
    m_currentStartTime = {};
}

const std::vector<long long>& Benchmarker::times()
{
	return m_benchmarks;
}

float Benchmarker::averageTime()
{
    if (m_benchmarks.empty()) {
        return 0;
    }

    auto const count = static_cast<float>(m_benchmarks.size());
    return static_cast<float>(std::reduce(m_benchmarks.begin(), m_benchmarks.end())) / count;
}
