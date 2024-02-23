#include "latency_helper.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <numeric>

void calculateAndPrintLatencyParameters (const std::vector<std::chrono::time_point<std::chrono::high_resolution_clock>>& startPoints,
                                        const std::vector<std::chrono::time_point<std::chrono::high_resolution_clock>>& stopPoints)
{
    if (startPoints.size() != stopPoints.size())
    {
        std::cout<< "could not calculate latencies, vectors have different length";
        return;
    }

    uint64_t sum = 0;
    uint32_t min = std::chrono::duration_cast<std::chrono::microseconds>(stopPoints[0] - startPoints[0]).count();
    uint32_t max = 0;
    for (size_t i = 0; i < startPoints.size(); i++)
    {
        auto latency = std::chrono::duration_cast<std::chrono::microseconds>(stopPoints[i] - startPoints[i]).count();
        sum = sum + latency;
        if (min > latency) { min = latency; }
        if (max < latency) { max = latency; }
    }
    auto mean = double(sum) / startPoints.size();

    std::cout << "Latency[us]: mean " << std::fixed << std::setprecision(2) << mean << " max " <<max << " min " << min << std::endl;
}

void calculateAndPrintLatencyParameters(const std::vector<uint32_t>& intervalsInMicroseconds)
{
    auto sum = std::accumulate(intervalsInMicroseconds.cbegin(), intervalsInMicroseconds.cend(), 0);
    double mean = double(sum) / intervalsInMicroseconds.size();
    const auto min_max  = std::minmax_element(intervalsInMicroseconds.begin(), intervalsInMicroseconds.end());
    std::cout << "Latency[us]: mean " << std::fixed << std::setprecision(2) << mean << " max " << *(min_max.second) << " min " << *(min_max.first) << std::endl;
}
