#include "ScheduleManager.h"
#include "RoutePlanner.h"

void ScheduleManager::addSchedule(const ScheduleEntry& s) {
    schedules.push_back(s);
}

ScheduleEntry ScheduleManager::getCopy(int index) const {
    return schedules.at(index);
}

int ScheduleManager::getSize() const {
    return static_cast<int>(schedules.size());
}

void ScheduleManager::generateListFromPlanner(RoutePlanner& planner) {
    schedules.clear();

    ShuttleManager& shuttleMgr = planner.getShuttleManager();
    PassengerManager& passengerMgr = planner.getPassengerManager();
    Scheduler& scheduler = planner.getScheduler();

    std::vector<Shuttle> shuttles;
    for (int i = 0; i < shuttleMgr.getSize(); ++i) {
        shuttles.push_back(shuttleMgr.getCopy(i));
    }

    std::vector<Passenger> passengers;
    for (int i = 0; i < passengerMgr.getSize(); ++i) {
        passengers.push_back(passengerMgr.getCopy(i));
    }

    auto results = scheduler.computeSchedule(shuttles, passengers);
    for (auto& entry : results) {
        schedules.push_back(entry);
    }
}
