#ifndef PASSENGER_MANAGER_H
#define PASSENGER_MANAGER_H

#include <vector>
#include "Passenger.h"

// Owns the in-RAM collection of Passenger objects and CRUD operations on
// them, indexed by position - mirrors ShuttleManager for consistency.
class PassengerManager {
private:
    std::vector<Passenger> passengers;

public:
    void addPassenger(const Passenger& p);
    void editPassenger(int index, const Passenger& p);
    void deletePassenger(int index);

    Passenger getCopy(int index) const;
    int getSize() const;
};

#endif
