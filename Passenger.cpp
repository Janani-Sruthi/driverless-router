#include "Passenger.h"
#include "Vehicle.h"
#include <algorithm>

namespace {
    // Req 4: group size is any positive number up to a maximum of 15 pax.
    int clampGroupSize(int size) {
        return std::max(1, std::min(size, 15));
    }
}

Passenger::Passenger(const std::string& qNum, std::shared_ptr<Location> dest, Time time, int size)
    : Traveller(qNum, time), destination(dest), groupSize(clampGroupSize(size)) {
}

std::shared_ptr<Location> Passenger::getDestination() const {
    return destination;
}

int Passenger::getGroupSize() const {
    return groupSize;
}

bool Passenger::canBoard(const Vehicle& vehicle) const {
    return vehicle.canServe(*destination, getArrivalTime());
}
