#include "RoutePlanner.h"

RoutePlanner::RoutePlanner() {}

void RoutePlanner::setDataFolderPath(const std::string& path) {
    fileHandler.setDataFolderPath(path);
}

bool RoutePlanner::loadData() {
    if (fileHandler.getDataFolderPath().empty()) {
        return false;
    }

    std::vector<Shuttle> loadedShuttles = fileHandler.loadShuttles(locationMgr);
    std::vector<Passenger> loadedPassengers = fileHandler.loadPassengers(locationMgr);

    // Replace whatever was in RAM with the freshly loaded data.
    shuttleMgr.getAll() = loadedShuttles;
    passengerMgr.getAll() = loadedPassengers;

    return true;
}

void RoutePlanner::computeSchedule() {
    currentSchedule = scheduler.computeSchedule(shuttleMgr.getAll(), passengerMgr.getAll());
}

const Schedule& RoutePlanner::getSchedule() const {
    return currentSchedule;
}

bool RoutePlanner::saveSchedule(const std::string& outputPath) const {
    return fileHandler.saveSchedule(outputPath, currentSchedule, shuttleMgr.getAll(), passengerMgr.getAll());
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