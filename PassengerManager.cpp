#include "PassengerManager.h"
#include <stdexcept>

void PassengerManager::addPassenger(const Passenger& p) {
    passengers.push_back(p);
}

void PassengerManager::editPassenger(int index, const Passenger& p) {
    if (index < 0 || index >= static_cast<int>(passengers.size())) {
        throw std::out_of_range("Passenger index out of range");
    }
    passengers[index] = p;
}

void PassengerManager::deletePassenger(int index) {
    if (index < 0 || index >= static_cast<int>(passengers.size())) {
        throw std::out_of_range("Passenger index out of range");
    }
    passengers.erase(passengers.begin() + index);
}

Passenger PassengerManager::getCopy(int index) const {
    if (index < 0 || index >= static_cast<int>(passengers.size())) {
        throw std::out_of_range("Passenger index out of range");
    }
    return passengers[index];
}

int PassengerManager::getSize() const {
    return static_cast<int>(passengers.size());
}
