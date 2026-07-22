#ifndef SHUTTLE_FACTORY_H
#define SHUTTLE_FACTORY_H

#include <memory>
#include <string>
#include "Shuttle.h"
#include "Location.h"
#include "Time.h"

// Centralises Shuttle creation so seating capacity per model/type lives
// in one place instead of being duplicated at every call site.
class ShuttleFactory {
public:
    // Throws std::invalid_argument if `time` falls outside the shuttle
    // operating hours (Req 3: 6:00am-11:59pm) - keeps that validation in
    // one place rather than scattered across FileHandler and MainUI.
    static Shuttle createShuttle(const std::string& type, const std::string& label,
        std::shared_ptr<Location> point, Time time);
};

#endif
