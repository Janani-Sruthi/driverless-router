#include "LocationManager.h"

LocationManager::LocationManager() {}

void LocationManager::addLocation(const std::string& name) {
    if (!exists(name)) {
        locations.push_back(Location(name));
    }
}

Location* LocationManager::findByName(const std::string& name) {
    for (auto& loc : locations) {
        if (loc.getName() == name) {
            return &loc;
        }
    }
    return nullptr;
}

bool LocationManager::exists(const std::string& name) const {
    for (const auto& loc : locations) {
        if (loc.getName() == name) {
            return true;
        }
    }
    return false;
}

std::vector<Location>& LocationManager::getAll() {
    return locations;
}

const std::vector<Location>& LocationManager::getAll() const {
    return locations;
}