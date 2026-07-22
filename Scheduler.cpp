#include "Scheduler.h"

Scheduler::Scheduler() {}

Schedule Scheduler::computeSchedule(std::vector<Shuttle>& shuttles, std::vector<Passenger>& passengers) {
    Schedule schedule;

    for (auto& passenger : passengers) {
        if (passenger.getIsMatched()) {
            continue; // already paired in a previous run
        }

        for (auto& shuttle : shuttles) {
            if (shuttle.getIsMatched()) {
                continue;
            }

            bool sameLocation = shuttle.getChargingPoint().getName() == passenger.getDestination().getName();
            bool sameTime = shuttle.getArrivalTime() == passenger.getArrivalTime();

            if (sameLocation && sameTime) {
                shuttle.setMatched(passenger.getQNumber());
                passenger.setMatched(shuttle.getLabel());
                schedule.addPair(shuttle.getLabel(), passenger.getQNumber());
                break; // this passenger is matched; move to the next one
            }
        }
    }

    return schedule;
}