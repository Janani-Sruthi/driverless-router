#include "Vehicle.h"

Vehicle::Vehicle(const std::string& label, Time time)
    : label(label), arrivalTime(time) {
}

const std::string& Vehicle::getLabel() const {
    return label;
}

const Time& Vehicle::getArrivalTime() const {
    return arrivalTime;
}
