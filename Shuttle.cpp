#include "Shuttle.h"

Shuttle::Shuttle(const std::string& label, const Location& point, const std::string& time)
    : Vehicle(label, time), chargingPoint(point), isMatched(false), assignedPassengerId("") {
}

void Shuttle::setMatched(const std::string& passengerId) {
    assignedPassengerId = passengerId;
    isMatched = true;
}

bool Shuttle::getIsMatched() const {
    return isMatched;
}

std::string Shuttle::getAssignedPassengerId() const {
    return assignedPassengerId;
}

Location Shuttle::getChargingPoint() const {
    return chargingPoint;
}