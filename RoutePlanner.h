#ifndef ROUTE_PLANNER_H
#define ROUTE_PLANNER_H

#include "ShuttleManager.h"
#include "PassengerManager.h"
#include "LocationManager.h"
#include "Scheduler.h"
#include "FileHandler.h"
#include "Schedule.h"

// Thin coordinator. Holds exactly one instance of each manager/service and
// forwards work to them — it no longer owns business logic itself. This is
// the fix for the original God Class: storage, validation, scheduling, and
// editing are now each somebody else's job.
class RoutePlanner {
private:
    ShuttleManager shuttleMgr;
    PassengerManager passengerMgr;
    LocationManager locationMgr;
    Scheduler scheduler;
    FileHandler fileHandler;
    Schedule currentSchedule;

public:
    RoutePlanner();

    // Delegated accessors — main.cpp/menu code goes through these rather
    // than reaching into the managers directly, keeping RoutePlanner as the
    // single entry point for the rest of the application.
    void setDataFolderPath(const std::string& path);
    bool loadData(); // loads both files via FileHandler into the two managers

    void computeSchedule();
    const Schedule& getSchedule() const;

    bool saveSchedule(const std::string& outputPath) const;

    ShuttleManager& getShuttleManager();
    PassengerManager& getPassengerManager();
    LocationManager& getLocationManager();
};

#endif