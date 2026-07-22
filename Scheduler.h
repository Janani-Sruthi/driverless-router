#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include "Shuttle.h"
#include "Passenger.h"
#include "ScheduleEntry.h"

class ISchedulingStrategy; // forward declaration - stored by non-owning pointer

// Strategy-pattern context: holds a pointer to the currently active
// ISchedulingStrategy and delegates computeSchedule() to it. Does not own
// the strategy object - RoutePlanner owns the concrete strategy instances
// and just points the Scheduler at whichever one is active.
class Scheduler {
private:
    ISchedulingStrategy* strategy;

public:
    Scheduler();

    void setStrategy(ISchedulingStrategy* strategy);

    std::vector<ScheduleEntry> computeSchedule(
        const std::vector<Shuttle>& shuttles,
        const std::vector<Passenger>& passengers) const;
};

#endif
