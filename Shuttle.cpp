#include "Shuttle.h"

Shuttle::Shuttle(const std::string& label, std::shared_ptr<Location> point, Time time,
    int capacity, const std::string& modelType)
    : Vehicle(label, time), chargingPoint(point), capacity(capacity), modelType(modelType) {
}

std::shared_ptr<Location> Shuttle::getChargingPoint() const {
    return chargingPoint;
}

int Shuttle::getCapacity() const {
    return capacity;
}

const std::string& Shuttle::getModelType() const {
    return modelType;
}

bool Shuttle::canServe(const Location& destination, const Time& requiredTime) const {
    if (chargingPoint->getName() != destination.getName()) {
        return false;
    }
    int lead = getArrivalTime().minutesEarly(requiredTime);
    return lead >= 0 && lead <= kMaxEarlyMinutes;
}
