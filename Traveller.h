#ifndef TRAVELLER_H
#define TRAVELLER_H

#include <string>
#include "Time.h"

class Vehicle; // forward declaration - only needed by reference here

// Abstract base for anyone/anything with a queue number and an arrival
// time. canBoard() is the hook each concrete traveller type uses to ask
// "can I get on this particular vehicle?"
class Traveller {
protected:
    std::string qNumber;
    Time arrivalTime;

public:
    Traveller(const std::string& qNum, Time time);
    virtual ~Traveller() = default;

    const std::string& getQNumber() const;
    const Time& getArrivalTime() const;

    virtual bool canBoard(const Vehicle& vehicle) const = 0;
};

#endif
