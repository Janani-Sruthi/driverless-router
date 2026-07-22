#ifndef SHUTTLE_H
#define SHUTTLE_H

#include <memory>
#include <string>
#include "Vehicle.h"
#include "Location.h"

// Shuttle IS-A Vehicle. No occupancy tracking lives here any more -
// per the UML, capacity is just a static ceiling; how many seats are
// actually used during matching is bookkeeping the scheduling strategy
// does locally, not state the Shuttle carries around.
class Shuttle : public Vehicle {
private:
    std::shared_ptr<Location> chargingPoint;
    int capacity;
    std::string modelType;

    // Req 5: a passenger may arrive up to this many minutes before their
    // requested time, but never after it.
    static constexpr int kMaxEarlyMinutes = 10;

public:
    Shuttle(const std::string& label, std::shared_ptr<Location> point, Time time,
        int capacity, const std::string& modelType);

    std::shared_ptr<Location> getChargingPoint() const;
    int getCapacity() const;
    const std::string& getModelType() const;

    // True if this shuttle's charging point matches destination and its
    // arrival is no more than kMaxEarlyMinutes before requiredTime and
    // never after it (midnight-safe via Time::minutesEarly). Does NOT
    // check seating - callers track occupancy themselves.
    bool canServe(const Location& destination, const Time& requiredTime) const override;
};

#endif
