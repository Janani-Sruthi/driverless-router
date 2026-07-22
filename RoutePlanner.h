#ifndef ROUTE_PLANNER_H
#define ROUTE_PLANNER_H

#include <string>
#include "ShuttleManager.h"
#include "PassengerManager.h"
#include "LocationManager.h"
#include "ScheduleManager.h"
#include "FileHandler.h"
#include "Scheduler.h"
#include "ArrivalTimeStrategy.h"
#include "MinDispatchStrategy.h"

// Thin coordinator: holds one instance of each manager/service, plus the
// Scheduler and the concrete strategy objects it can point the Scheduler
// at. Owning the strategies here (rather than in Scheduler, which only
// holds a raw non-owning pointer) keeps their lifetime simple.
class RoutePlanner {
private:
    ShuttleManager shuttleMgr;
    PassengerManager passengerMgr;
    LocationManager locationMgr;
    ScheduleManager scheduleMgr;
    FileHandler fileHandler;
    Scheduler scheduler;

    ArrivalTimeStrategy arrivalTimeStrategy;
    MinDispatchStrategy minDispatchStrategy;

public:
    RoutePlanner();

    // Loads shuttle.txt/passenger.txt from dataFolderPath, matches them
    // with the current strategy, and prints the result.
    void run(const std::string& dataFolderPath);

    // Recomputes scheduleMgr's contents via scheduleMgr.generateListFromPlanner(*this).
    void executeMatching();

    // Prints the current schedule (matched pairs + an unmatched count).
    void displayStuff() const;

    // Convenience: point the Scheduler at one of the two built-in
    // strategies. Clears the existing schedule since it was computed
    // under the old strategy's assumptions.
    void useArrivalTimeStrategy();
    void useMinDispatchStrategy();

    // Convenience save, since the UML doesn't give RoutePlanner its own
    // save method but MainUI needs one to call.
    bool saveSchedule(const std::string& path) const;

    // Req 10: saves current in-RAM shuttle/passenger data to new files
    // (never overwrites the originals - caller picks the paths).
    bool saveShuttleAndPassengerData(const std::string& shuttlePath, const std::string& passengerPath) const;

    // Accessors used by ScheduleManager::generateListFromPlanner and by
    // MainUI for add/edit/delete flows.
    ShuttleManager& getShuttleManager();
    PassengerManager& getPassengerManager();
    LocationManager& getLocationManager();
    Scheduler& getScheduler();
    const ScheduleManager& getScheduleManager() const;
};

#endif
