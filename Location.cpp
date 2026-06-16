#include "Location.h"

Location::Location() : name("") {}

Location::Location(const std::string& name) : name(name) {}

std::string Location::getName() const {
    return name;
}

bool Location::operator==(const Location& other) const {
    return name == other.name;
}