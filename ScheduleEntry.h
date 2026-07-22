#ifndef SCHEDULE_ENTRY_H
#define SCHEDULE_ENTRY_H

#include "Passenger.h"
#include "Shuttle.h"

// A single passenger-shuttle pairing produced by a scheduling strategy.
// Note this stores Passenger/Shuttle by value (snapshots at match time),
// not shared_ptr, per the UML.
class ScheduleEntry {
private:
    Passenger passengerItem;
    Shuttle shuttleItem;
    bool matchStatus;

public:
    ScheduleEntry(const Passenger& p, const Shuttle& s, bool matched);

    bool isMatched() const;
    const Passenger& getPassenger() const;
    const Shuttle& getShuttle() const;
};

#endif
