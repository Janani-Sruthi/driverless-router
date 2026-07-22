#ifndef LOCATION_H
#define LOCATION_H

#include <string>

// charging point / destination in the town.
//Pure data class, no display logic 
class Location {
private:
    std::string name;

public:
    Location();
    explicit Location(const std::string& name);

    std::string getName() const;

    //Location can be compared/found inside vectors and used as a map key.
    bool operator==(const Location& other) const;
};

#endif