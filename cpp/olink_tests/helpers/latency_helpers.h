#pragma once

#include <memory>
#include <vector>
#include <chrono>

using chrono_hr_timepoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

/**
 * Calculates mean, min and max parameters for events duration described in two vectors, one with events start timepoint and one with events stop timepoints.
 * Assumes that the position in a vector identifies the event. For an event A position of start in startPoints must be same as its stop in stopPoints
 * @param startPoints timepoints for start of events
 * @param stopPoints timepoints for stop of events
*/
void calculateAndPrintLatencyParameters (const std::vector<chrono_hr_timepoint>& startPoints,
                                         const std::vector<chrono_hr_timepoint>& stopPoints);


/**
 * Calculates mean, min and max parameters for a vector
 * @param intervalsInMicroseconds an interval time in microseconds.
*/
void calculateAndPrintLatencyParameters(const std::vector<uint32_t>& intervalsInMicroseconds);
