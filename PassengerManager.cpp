#include "PassengerManager.h"
#include <algorithm>

PassengerManager::PassengerManager() {}

void PassengerManager::addPassenger(const std::string& qNum, const Location& dest, const std::string& time) {
    passengers.push_back(Passenger(qNum, dest, time));
}

bool PassengerManager::editPassenger(const std::string& qNum, const Location& newDest, const std::string& newTime) {
    Passenger* existing = findByQNumber(qNum);
    if (existing == nullptr) {
        return false;
    }
    bool wasMatched = existing->getIsMatched();
    std::string assignedId = existing->getAssignedShuttleId();

    Passenger updated(qNum, newDest, newTime);
    if (wasMatched) {
        updated.setMatched(assignedId);
    }

    for (auto& p : passengers) {
        if (p.getQNumber() == qNum) {
            p = updated;
            return true;
        }
    }
    return false;
}

bool PassengerManager::deletePassenger(const std::string& qNum) {
    auto it = std::remove_if(passengers.begin(), passengers.end(),
        [&qNum](const Passenger& p) { return p.getQNumber() == qNum; });
    if (it == passengers.end()) {
        return false;
    }
    passengers.erase(it, passengers.end());
    return true;
}

std::vector<Passenger>& PassengerManager::getAll() {
    return passengers;
}

const std::vector<Passenger>& PassengerManager::getAll() const {
    return passengers;
}

Passenger* PassengerManager::findByQNumber(const std::string& qNum) {
    for (auto& p : passengers) {
        if (p.getQNumber() == qNum) {
            return &p;
        }
    }
    return nullptr;
}