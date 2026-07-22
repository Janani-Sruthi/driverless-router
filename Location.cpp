#include "Location.h"

Location::Location(const std::string& name) : name(name) {}

const std::string& Location::getName() const {
    return name;
}
