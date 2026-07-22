#ifndef LOCATION_H
#define LOCATION_H

#include <string>

// A charging point / destination in the town. Pure data class.
class Location {
private:
    std::string name;

public:
    explicit Location(const std::string& name);

    const std::string& getName() const;
};

#endif
