#include "ShuttleManager.h"
#include <stdexcept>

void ShuttleManager::addShuttle(const Shuttle& s) {
    shuttles.push_back(s);
}

void ShuttleManager::editShuttle(int index, const Shuttle& s) {
    if (index < 0 || index >= static_cast<int>(shuttles.size())) {
        throw std::out_of_range("Shuttle index out of range");
    }
    shuttles[index] = s;
}

void ShuttleManager::deleteShuttle(int index) {
    if (index < 0 || index >= static_cast<int>(shuttles.size())) {
        throw std::out_of_range("Shuttle index out of range");
    }
    shuttles.erase(shuttles.begin() + index);
}

Shuttle ShuttleManager::getCopy(int index) const {
    if (index < 0 || index >= static_cast<int>(shuttles.size())) {
        throw std::out_of_range("Shuttle index out of range");
    }
    return shuttles[index];
}

int ShuttleManager::getSize() const {
    return static_cast<int>(shuttles.size());
}
