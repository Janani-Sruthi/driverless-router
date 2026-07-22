#ifndef ARRIVAL_TIME_STRATEGY_H
#define ARRIVAL_TIME_STRATEGY_H

#include "ISchedulingStrategy.h"

// Matches each Passenger to the Shuttle that can serve them (same
// destination, within the wait-time window) whose arrival time is
// closest to the passenger's own, subject to seating capacity.
class ArrivalTimeStrategy : public ISchedulingStrategy {
public:
    std::vector<ScheduleEntry> computeSchedule(
        const std::vector<Shuttle>& shuttles,
        const std::vector<Passenger>& passengers) override;
};

#endif
