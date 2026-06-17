#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Shuttle.h"
#include "Passenger.h"
#include "Schedule.h"
#include <vector>

// Pure matching logic. Reads from ShuttleManager/PassengerManager's data
// (passed in by reference) and produces a Schedule, but never owns the
// underlying vectors itself — that ownership stays with the managers.
class Scheduler {
public:
    Scheduler();

    // Matches each unmatched Passenger to an available Shuttle sharing the
    // same destination/charging point and the same arrival time.
    // Mutates the Shuttle/Passenger objects in place (sets isMatched) and
    // returns a Schedule recording the pairs by ID.
    Schedule computeSchedule(std::vector<Shuttle>& shuttles, std::vector<Passenger>& passengers);
};

#endif