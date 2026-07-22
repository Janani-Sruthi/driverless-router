#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include "Time.h"

class Location; // forward declaration - only needed by reference here

// Abstract base for any vehicle entity in the system. canServe() is the
// hook each concrete vehicle type uses to say whether it can pick up a
// traveller headed to a given destination at a given time.
class Vehicle {
protected:
    std::string label;
    Time arrivalTime;

public:
    Vehicle(const std::string& label, Time time);
    virtual ~Vehicle() = default;

    const std::string& getLabel() const;
    const Time& getArrivalTime() const;

    virtual bool canServe(const Location& destination, const Time& requiredTime) const = 0;
};

#endif
