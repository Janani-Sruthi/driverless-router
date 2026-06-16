#ifndef PASSENGER_H
#define PASSENGER_H

#include "Person.h"
#include "Location.h"

// Passenger IS-A Person, with trip-specific data (destination) added here
// rather than pushed up into the shared base class.
class Passenger : public Person {
private:
    Location destination;
    bool isMatched;
    std::string assignedShuttleId; // ID only, never a raw Shuttle* — avoids
    // dangling references if a Shuttle is
    // deleted or moved elsewhere in memory.

public:
    Passenger(const std::string& qNum, const Location& dest, const std::string& time);

    void setMatched(const std::string& shuttleId);
    bool getIsMatched() const;
    std::string getAssignedShuttleId() const;
    Location getDestination() const;
};

#endif