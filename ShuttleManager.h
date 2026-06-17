#ifndef SHUTTLE_MANAGER_H
#define SHUTTLE_MANAGER_H

#include <string>
#include <vector>
#include "Shuttle.h"
#include "Location.h"

// Owns the in-RAM collection of Shuttle objects and all CRUD operations on
// them. Split out of RoutePlanner so that "managing shuttles" is a single,
// focused responsibility instead of one God Class doing everything.
class ShuttleManager {
private:
    std::vector<Shuttle> shuttles;

public:
    ShuttleManager();

    void addShuttle(const std::string& label, const Location& point, const std::string& time);
    bool editShuttle(const std::string& label, const Location& newPoint, const std::string& newTime);
    bool deleteShuttle(const std::string& label);

    std::vector<Shuttle>& getAll();
    const std::vector<Shuttle>& getAll() const;
    Shuttle* findByLabel(const std::string& label);
};

#endif 