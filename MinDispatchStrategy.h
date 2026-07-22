#ifndef MIN_DISPATCH_STRATEGY_H
#define MIN_DISPATCH_STRATEGY_H

#include "ISchedulingStrategy.h"

// Fills each eligible shuttle to capacity before moving on to the next
// one, minimising how many shuttles end up carrying passengers.
class MinDispatchStrategy : public ISchedulingStrategy {
public:
    std::vector<ScheduleEntry> computeSchedule(
        const std::vector<Shuttle>& shuttles,
        const std::vector<Passenger>& passengers) override;
};

#endif
