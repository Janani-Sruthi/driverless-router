#ifndef LOCATION_MANAGER_H
#define LOCATION_MANAGER_H

#include <memory>
#include <string>
#include <vector>
#include "Location.h"

// Owns the known set of valid Locations, shared by pointer so every
// Shuttle/Passenger that refers to "Mall" refers to the exact same
// Location instance where possible.
class LocationManager {
private:
    std::vector<std::shared_ptr<Location>> locations;

public:
    // Returns the existing Location if `name` is already known, otherwise
    // creates, stores, and returns a new one.
    std::shared_ptr<Location> addLocation(const std::string& name);

    // Returns nullptr if no Location with that name is known.
    std::shared_ptr<Location> findByName(const std::string& name) const;
};

#endif
