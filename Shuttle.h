#ifndef SHUTTLE_H
#define SHUTTLE_H

#include "Vehicle.h"
#include "Location.h"

// Shuttle IS-A Vehicle, with the charging point typed as Location (not
// string) so the UML association to Location is consistent with the
// attribute that actually backs it.
class Shuttle : public Vehicle {
private:
    Location chargingPoint;
    bool isMatched;
    std::string assignedPassengerId;

public:
    Shuttle(const std::string& label, const Location& point, const std::string& time);

    void setMatched(const std::string& passengerId);
    bool getIsMatched() const;
    std::string getAssignedPassengerId() const;
    Location getChargingPoint() const;
};

#endif
