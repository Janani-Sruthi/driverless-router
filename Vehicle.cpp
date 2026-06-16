#include "Vehicle.h"

Vehicle::Vehicle(const std::string& label, const std::string& time)
    : label(label), arrivalTime(time) {
}

std::string Vehicle::getLabel() const {
    return label;
}

std::string Vehicle::getArrivalTime() const {
    return arrivalTime;
}