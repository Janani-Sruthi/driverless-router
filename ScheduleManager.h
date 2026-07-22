#ifndef SCHEDULE_MANAGER_H
#define SCHEDULE_MANAGER_H

#include <vector>
#include "ScheduleEntry.h"

class RoutePlanner; // forward declaration - avoids a header cycle with RoutePlanner.h

// Owns the current set of ScheduleEntry matches. generateListFromPlanner()
// pulls shuttles/passengers out of the RoutePlanner's managers, runs them
// through its Scheduler, and stores the results here.
class ScheduleManager {
private:
    std::vector<ScheduleEntry> schedules;

public:
    void addSchedule(const ScheduleEntry& s);
    ScheduleEntry getCopy(int index) const;
    int getSize() const;

    void generateListFromPlanner(RoutePlanner& planner);
};

#endif
