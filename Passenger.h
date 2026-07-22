#ifndef PASSENGER_H
#define PASSENGER_H

#include <memory>
#include "Traveller.h"
#include "Location.h"

// Passenger IS-A Traveller, with trip-specific data (destination, group
// size) added here rather than pushed into the shared base class.
class Passenger : public Traveller {
private:
    std::shared_ptr<Location> destination;
    int groupSize;

public:
    Passenger(const std::string& qNum, std::shared_ptr<Location> dest, Time time, int size);

    std::shared_ptr<Location> getDestination() const;
    int getGroupSize() const;

    // Delegates to vehicle.canServe(destination, arrivalTime) - a
    // passenger can board any vehicle willing to serve their trip.
    bool canBoard(const Vehicle& vehicle) const override;
};

#endif
