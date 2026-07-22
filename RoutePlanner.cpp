#include "RoutePlanner.h"
#include <iostream>

RoutePlanner::RoutePlanner() {
    // Sensible default so the app is usable before anyone picks a strategy.
    scheduler.setStrategy(&arrivalTimeStrategy);
}

void RoutePlanner::run(const std::string& dataFolderPath) {
    auto shuttles = fileHandler.loadShuttles(dataFolderPath + "/shuttle.txt");
    for (auto& s : shuttles) shuttleMgr.addShuttle(s);

    auto passengers = fileHandler.loadPassengers(dataFolderPath + "/passenger.txt");
    for (auto& p : passengers) passengerMgr.addPassenger(p);

    executeMatching();
    displayStuff();
}

void RoutePlanner::executeMatching() {
    scheduleMgr.generateListFromPlanner(*this);
}

void RoutePlanner::displayStuff() const {
    int matched = scheduleMgr.getSize();

    if (matched == 0) {
        std::cout << "No matches yet - load data and run matching first.\n";
        return;
    }

    for (int i = 0; i < matched; ++i) {
        ScheduleEntry entry = scheduleMgr.getCopy(i);
        const Passenger& p = entry.getPassenger();
        const Shuttle& s = entry.getShuttle();
        std::cout << p.getQNumber() << " (group of " << p.getGroupSize() << ")"
            << " -> Shuttle " << s.getLabel()
            << " @ " << s.getChargingPoint()->getName()
            << " [matched=" << (entry.isMatched() ? "yes" : "no") << "]\n";
    }
}

void RoutePlanner::useArrivalTimeStrategy() {
    scheduler.setStrategy(&arrivalTimeStrategy);
}

void RoutePlanner::useMinDispatchStrategy() {
    scheduler.setStrategy(&minDispatchStrategy);
}

bool RoutePlanner::saveSchedule(const std::string& path) const {
    std::vector<ScheduleEntry> entries;
    for (int i = 0; i < scheduleMgr.getSize(); ++i) {
        entries.push_back(scheduleMgr.getCopy(i));
    }
    fileHandler.saveSchedule(path, entries);
    return true;
}

bool RoutePlanner::saveShuttleAndPassengerData(const std::string& shuttlePath, const std::string& passengerPath) const {
    std::vector<Shuttle> shuttles;
    for (int i = 0; i < shuttleMgr.getSize(); ++i) {
        shuttles.push_back(shuttleMgr.getCopy(i));
    }
    std::vector<Passenger> passengers;
    for (int i = 0; i < passengerMgr.getSize(); ++i) {
        passengers.push_back(passengerMgr.getCopy(i));
    }
    fileHandler.saveShuttles(shuttlePath, shuttles);
    fileHandler.savePassengers(passengerPath, passengers);
    return true;
}

ShuttleManager& RoutePlanner::getShuttleManager() {
    return shuttleMgr;
}

PassengerManager& RoutePlanner::getPassengerManager() {
    return passengerMgr;
}

LocationManager& RoutePlanner::getLocationManager() {
    return locationMgr;
}

Scheduler& RoutePlanner::getScheduler() {
    return scheduler;
}

const ScheduleManager& RoutePlanner::getScheduleManager() const {
    return scheduleMgr;
}
