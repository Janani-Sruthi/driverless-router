#include "ShuttleManager.h"
#include <algorithm>

ShuttleManager::ShuttleManager() {}

void ShuttleManager::addShuttle(const std::string& label, const Location& point, const std::string& time) {
    shuttles.push_back(Shuttle(label, point, time));
}

bool ShuttleManager::editShuttle(const std::string& label, const Location& newPoint, const std::string& newTime) {
    Shuttle* existing = findByLabel(label);
    if (existing == nullptr) {
        return false;
    }
    // Shuttle has no setters for chargingPoint/arrivalTime (immutable after
    // construction in this design), so "editing" replaces the object while
    // preserving its match state.
    bool wasMatched = existing->getIsMatched();
    std::string assignedId = existing->getAssignedPassengerId();

    Shuttle updated(label, newPoint, newTime);
    if (wasMatched) {
        updated.setMatched(assignedId);
    }

    for (auto& s : shuttles) {
        if (s.getLabel() == label) {
            s = updated;
            return true;
        }
    }
    return false;
}

bool ShuttleManager::deleteShuttle(const std::string& label) {
    auto it = std::remove_if(shuttles.begin(), shuttles.end(),
        [&label](const Shuttle& s) { return s.getLabel() == label; });
    if (it == shuttles.end()) {
        return false;
    }
    shuttles.erase(it, shuttles.end());
    return true;
}

std::vector<Shuttle>& ShuttleManager::getAll() {
    return shuttles;
}

const std::vector<Shuttle>& ShuttleManager::getAll() const {
    return shuttles;
}

Shuttle* ShuttleManager::findByLabel(const std::string& label) {
    for (auto& s : shuttles) {
        if (s.getLabel() == label) {
            return &s;
        }
    }
    return nullptr;
}