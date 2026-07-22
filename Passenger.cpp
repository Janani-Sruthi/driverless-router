#include "Passenger.h"

Passenger::Passenger(const std::string& qNum, const Location& dest, const std::string& time)
    : Person(qNum, time), destination(dest), isMatched(false), assignedShuttleId("") {
}

void Passenger::setMatched(const std::string& shuttleId) {
    assignedShuttleId = shuttleId;
    isMatched = true;
}

bool Passenger::getIsMatched() const {
    return isMatched;
}

std::string Passenger::getAssignedShuttleId() const {
    return assignedShuttleId;
}

Location Passenger::getDestination() const {
    return destination;
}