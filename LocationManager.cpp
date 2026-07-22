#include "LocationManager.h"

std::shared_ptr<Location> LocationManager::addLocation(const std::string& name) {
    auto existing = findByName(name);
    if (existing) {
        return existing;
    }
    auto loc = std::make_shared<Location>(name);
    locations.push_back(loc);
    return loc;
}

std::shared_ptr<Location> LocationManager::findByName(const std::string& name) const {
    for (const auto& loc : locations) {
        if (loc->getName() == name) {
            return loc;
        }
    }
    return nullptr;
}
