#include "ShuttleFactory.h"
#include <stdexcept>

// Req 2: Small=2, Family=5, Premium=12. Unknown types fall back to
// Family's capacity rather than failing outright.
static int capacityForType(const std::string& type) {
    if (type == "Small") return 2;
    if (type == "Family") return 5;
    if (type == "Premium") return 12;
    return 5;
}

Shuttle ShuttleFactory::createShuttle(const std::string& type, const std::string& label,
    std::shared_ptr<Location> point, Time time) {
    if (!time.isWithinOperatingHours()) {
        throw std::invalid_argument("Shuttle " + label + " arrival time is outside operating hours (6:00am-11:59pm)");
    }
    int capacity = capacityForType(type);
    return Shuttle(label, point, time, capacity, type);
}
