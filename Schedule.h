#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <string>
#include <vector>
#include <utility>
#include "Shuttle.h"
#include "Passenger.h"

// Stores matched Shuttle-Passenger pairs by ID (label / Q-number). This avoids dangling references if the original Shuttle or
// Passenger objects are later deleted, edited, or the underlying vector
// reallocates and moves them in memory.
class Schedule {
private:
    std::vector<std::pair<std::string, std::string>> matchedPairs; // (shuttleLabel, passengerQNum)

public:
    Schedule();

    void addPair(const std::string& shuttleLabel, const std::string& passengerQNum);
    std::vector<std::pair<std::string, std::string>> getMatchedPairs() const;

    std::vector<std::string> getUnmatchedShuttles(const std::vector<Shuttle>& allShuttles) const;
    std::vector<std::string> getUnmatchedPassengers(const std::vector<Passenger>& allPassengers) const;
};

#endif // SCHEDULE_H