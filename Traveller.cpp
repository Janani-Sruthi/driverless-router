#include "Traveller.h"

Traveller::Traveller(const std::string& qNum, Time time)
    : qNumber(qNum), arrivalTime(time) {
}

const std::string& Traveller::getQNumber() const {
    return qNumber;
}

const Time& Traveller::getArrivalTime() const {
    return arrivalTime;
}
