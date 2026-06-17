#ifndef PASSENGER_MANAGER_H
#define PASSENGER_MANAGER_H

#include <string>
#include <vector>
#include "Passenger.h"
#include "Location.h"

// Owns the in-RAM collection of Passenger objects and all CRUD operations
// on them. Mirrors ShuttleManager's structure for consistency.
class PassengerManager {
private:
    std::vector<Passenger> passengers;

public:
    PassengerManager();

    void addPassenger(const std::string& qNum, const Location& dest, const std::string& time);
    bool editPassenger(const std::string& qNum, const Location& newDest, const std::string& newTime);
    bool deletePassenger(const std::string& qNum);

    std::vector<Passenger>& getAll();
    const std::vector<Passenger>& getAll() const;
    Passenger* findByQNumber(const std::string& qNum);
};

#endif 