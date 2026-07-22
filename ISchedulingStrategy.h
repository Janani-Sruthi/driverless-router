#ifndef I_SCHEDULING_STRATEGY_H
#define I_SCHEDULING_STRATEGY_H

#include <vector>
#include "Shuttle.h"
#include "Passenger.h"
#include "ScheduleEntry.h"

// Strategy interface: a swappable algorithm for turning a set of Shuttles
// and Passengers into a list of ScheduleEntry matches.
class ISchedulingStrategy {
public:
    virtual ~ISchedulingStrategy() = default;

    virtual std::vector<ScheduleEntry> computeSchedule(
        const std::vector<Shuttle>& shuttles,
        const std::vector<Passenger>& passengers) = 0;
};

#endif
