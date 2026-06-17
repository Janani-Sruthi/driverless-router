#ifndef LOC_MANAGER_H
#define LOC_MANAGER_H

#include <string>
#include <vector>
#include "Location.h"

// Owns the known set of valid Locations (charging points / destinations)
// in the town. Used to validate Shuttle/Passenger data at load time instead
// of letting unrecognised location strings pass through silently.
class LocationManager {
private:
    std::vector<Location> locations;

public:
    LocationManager();

    void addLocation(const std::string& name);
    Location* findByName(const std::string& name);
    bool exists(const std::string& name) const;

    std::vector<Location>& getAll();
    const std::vector<Location>& getAll() const;
};

#endif 