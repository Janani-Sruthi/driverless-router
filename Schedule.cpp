#include "Schedule.h"

Schedule::Schedule() {}

void Schedule::addPair(const std::string& shuttleLabel, const std::string& passengerQNum) {
    matchedPairs.push_back(std::make_pair(shuttleLabel, passengerQNum));
}

std::vector<std::pair<std::string, std::string>> Schedule::getMatchedPairs() const {
    return matchedPairs;
}

std::vector<std::string> Schedule::getUnmatchedShuttles(const std::vector<Shuttle>& allShuttles) const {
    std::vector<std::string> unmatched;
    for (const auto& shuttle : allShuttles) {
        if (!shuttle.getIsMatched()) {
            unmatched.push_back(shuttle.getLabel());
        }
    }
    return unmatched;
}

std::vector<std::string> Schedule::getUnmatchedPassengers(const std::vector<Passenger>& allPassengers) const {
    std::vector<std::string> unmatched;
    for (const auto& passenger : allPassengers) {
        if (!passenger.getIsMatched()) {
            unmatched.push_back(passenger.getQNumber());
        }
    }
    return unmatched;
}