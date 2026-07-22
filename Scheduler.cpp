#include "Scheduler.h"
#include "ISchedulingStrategy.h"

Scheduler::Scheduler() : strategy(nullptr) {}

void Scheduler::setStrategy(ISchedulingStrategy* newStrategy) {
    strategy = newStrategy;
}

std::vector<ScheduleEntry> Scheduler::computeSchedule(
    const std::vector<Shuttle>& shuttles,
    const std::vector<Passenger>& passengers) const {
    if (!strategy) {
        return {};
    }
    return strategy->computeSchedule(shuttles, passengers);
}
