#include "Person.h"

Person::Person(const std::string& qNum, const std::string& time)
    : qNumber(qNum), arrivalTime(time) {
}

std::string Person::getQNumber() const {
    return qNumber;
}

std::string Person::getArrivalTime() const {
    return arrivalTime;
}