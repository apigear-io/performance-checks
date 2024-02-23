#ifndef LATENCY_HELPER_H
#define LATENCY_HELPER_H

#include <memory>
#include <vector>
#include <chrono>


/**
 * Calculates mean, min and max parameters for events duration described in two vectors, one with events start timepoint and one with events stop timepoints.
 * Assumes that the position in a vector identifies the event. For an event A position of start in startPoints must be same as its stop in stopPoints
 * @param startPoints timepoints for start of events
 * @param stopPoints timepoints for stop of events
*/
void calculateAndPrintLatencyParameters (const std::vector<std::chrono::time_point<std::chrono::high_resolution_clock>>& startPoints,
                                        const std::vector<std::chrono::time_point<std::chrono::high_resolution_clock>>& stopPoints);


/**
 * Calculates mean, min and max parameters for a vector
 * @param intervalsInMicroseconds an interval time in microseconds.
*/
void calculateAndPrintLatencyParameters(const std::vector<uint32_t>& intervalsInMicroseconds);



#endif // LATENCY_HELPER_H
